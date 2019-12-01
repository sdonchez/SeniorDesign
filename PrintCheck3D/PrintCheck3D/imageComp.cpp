#include "imageComp.h"

imageComp::imageComp(cv::Mat image, model* model)
{
	src = image;
	currModel = *model;
	edgeThresh = 1;
	ratio = 3;
	kernelSize = 3;
	lowThreshold = 50;

	dst.create(src.size(), src.type());
	cvtColor(src, srcGray, COLOR_BGR2GRAY);

	edgeDetect();
}

imageComp::~imageComp()
{
}

void imageComp::edgeDetect()
{
	/// Reduce noise with a kernel 3x3
	blur(srcGray, detectedEdges, Size(3, 3));

	/// Canny detector
	Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold * ratio, kernelSize);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);
	src.copyTo(dst, detectedEdges);
	cv::imwrite("edges.jpg", dst); //save image to file
}

bool imageComp::compModel() 
{
	bool failedPrint;
	cv::Mat dest;
	cv::Mat currentModel = currModel.getMat();
	cv::bitwise_xor(dst, currentModel, dest); //may need to convert currModel into a cv::Mat
	if (cv::countNonZero(dst) > 0) //check non-0 pixels
		failedPrint = true;
	else
		failedPrint = false;
	return failedPrint;
}