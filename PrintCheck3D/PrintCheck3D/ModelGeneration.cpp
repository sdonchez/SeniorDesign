/*
*	ModelGeneration.c:
*       Responsible for generating the vertical outline of a model from G-code
*
*       Process:
*		Takes in G-code, read line-by-line, recognize if receiving arc code 
*       (if so find max of that arc using the center point and radius), store 
*       all values of an axis into array, stop feeding array when the command 
*       for a new layer is read (and store the layer height value). Find max 
*       and min of values in that array, store and graphically represent those 
*       points. Then clear the array and begin again, moving the height for the 
*       next points by the layer height. Once all points are processed, connect 
*       the dots to create the outline. 
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

#include "ModelGeneration.h"
int fd = 0; //file descriptor
/*
* readGcode: reads Gcode and stores the values from a specific axis into an array
* which then stores the min/max of each layer into arrays (or a single 2D array)
* that are returned
*/
void ModelGeneration::readGcode()
{
    int aval = serialDataAvail(fd);
    serialGetchar(fd);
    if (aval !< 0){
        for(int i = 0;i < 3 + 1; i++){
         fd[i]

        }
    }
    else{
        std::cout << "error number: " << errno;
    }
}

/*
* plotGcode: takes two arrays (or a single 2D array) and outputs (or stores) an 
* image of those pointswhich then stores the min/max of each layer into arrays 
* that are returned
*/
void ModelGeneration::plotGcode()
{
    
    
    xData.create(1, 100, CV_64F);//1 row, 100 columns, Double
    yData.create(1, 100, CV_64F);

    for(int i = 0; i<100; ++i)
    {
        xData.at<double>(i) = arrX[i];
        yData.at<double>(i) = arrY[i];
    }
    plot = plot::createPlot2d(xData, yData);
    plot->setPlotSize(100, 1000);
    plot->setMaxX(10);
    plot->setMinX(0);
    plot->setMaxY(100);
    plot->setMinY(-1);
    plot->render(display);
    imshow("Plot", display);

)       

}


