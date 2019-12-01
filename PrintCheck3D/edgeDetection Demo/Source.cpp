using namespace std;
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <raspicam/raspicam_cv.h>
#include "imageComp.h"
#include "model.h"

int main()
{
	raspicam::RaspiCam_Cv Camera;
	cv::Mat image; //create image object

	if (!Camera.open()) cerr << "Error opening the camera" << endl;
	//^camera connection error^
	Camera.setHorizontalFlip(true);
	Camera.setVerticalFlip(true);
	Camera.setExposureCompensation(25);

	Camera.grab(); //begin recieving data
	Camera.retrieve(image); //grab image
	Camera.release(); //stop recieving data
	cv::imwrite("raspicam_cv_image.jpg", image); //save image to file
	model* currModel = new model();
	imageComp ic = imageComp(image, currModel);
	if (ic.compModel() == false)
		cout << "image doesn't match model" << endl;
	else
		cout << "image matches model" << endl;
	return 0;
}