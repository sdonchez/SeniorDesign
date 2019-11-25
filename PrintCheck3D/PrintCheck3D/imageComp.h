#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "model.h"

using namespace cv;

class imageComp
{
public:
	imageComp(cv::Mat,model*);
	~imageComp();
	void edgeDetect();
	bool compModel();

private:
	Mat src, srcGray;
	Mat dst, detectedEdges;
	int edgeThresh;
	int lowThreshold;
	int const maxLowThreshold = 100;
	int ratio;
	int kernelSize;
	char* windowName;
	model currModel;
};

