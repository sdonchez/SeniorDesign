#include <raspicam/raspicam_cv.h>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;

int main() {
	cv::Mat image; //create image object
	raspicam::RaspiCam_Cv Camera;

	if (!Camera.open()) cerr << "Error opening the camera" << endl;
	//^camera connection error^

	Camera.grab(); //begin recieving data
	Camera.retrieve(image); //grab image
	Camera.release(); //stop recieving data
	cv::imwrite("raspicam_cv_image.jpg", image); //save image to file
	return 0;
}
