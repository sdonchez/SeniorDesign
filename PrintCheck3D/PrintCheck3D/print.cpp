/*
*	print.c:
*		Facilitates the monitoring of a printjob, and serves as the calling
*		class for the sending of commands to the printer via RAMBoInterface.h
********************************************************************************
*	This file is part of PrintCheck3D
*	Copyright(C) 2019 Stephen Donchez, Jared Rymsza, Robert Pink
*
*	This program is free software : you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.If not, see < https://www.gnu.org/licenses/>.
*******************************************************************************/

#include "print.h"


/*******************************************************************************
* print: sets up the various functionalities required to manage a print. Defines
*	a file to store the current image from the camera, as well as the current
*	model state. Also starts GCode transfer, and tells the webserver that
*	printing has commenced
*	@param RAMBoInteface *printerInterface: a pointer to the RAMBoInterface
*		object created by the main routine during startup
*	@returns: none
*	@note:
*	@see:
*******************************************************************************/
print::print(RAMBoInterface *printerInterface)
{
	this->printerInterface = *printerInterface;
	image = new cv::Mat;
	currModel = new model();
	printerInterface.startGcode();
	currConnection.printStarted();
}


print::~print()
{
	currConnection.printCompleted();
}

/*******************************************************************************
*  monitorPrint: loops through a process of checking the status of the printer,
*	comparing it to the expected appearence of the print, and taking action (or 
*	no action) depending on the results, before waiting and repeating this 
*	process.
*	@param none
*	@returns: none
*	@note:
*	@see:
*******************************************************************************/
void print::monitorPrint() {
	while (isPrinting) {
		printerInterface.fetchGcode();
		statusCheck();
		evaluatePrint();
		try {
			resultHandler();
		}
		catch (printFailureException e){
			printerInterface.stopPrint();
			percentComplete = 0;
			statusDescr = e.what;
		}
		catch (filamentOutException e) {
			printerInterface.pausePrint();
			statusDescr = e.what;
		}
		currConnection.upload(image, percentComplete, statusDescr);
		usleep(30000000);
	}
}

void print::statusCheck(){
//------------------Take a picture---------------------
        Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 ); //set camera params
        if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
        //^camera connection error^

        Camera.grab(); //begin recieving data
        Camera.retrieve(image); //grab image
        Camera.release(); //stop recieving data
        cv::imwrite("raspicam_cv_image.jpg",image); //save image to file

        //----------------Check photogate---------------------
        return filamentCheck();
}

/*******************************************************************************
* evaluatePrint: compares the two images to ensure the print is within bounds,
*	and sets the apropriate variable if there is a failure detected. Also 
*	calculates percent completion
*	@param none
*	@returns: none
*	@note:
*	@see:
*******************************************************************************/
void print::evaluatePrint() {
	int result = 0;
	imageComp currComp = new imageComp(image, currModel);
	
	if (currComp.match && filamentCheck)
		percentComplete = (currLine / totalLines) * 100;
	else
		percentComplete = 0;
}