#pragma once

/*
*	ModelGeneration.c:
*       Responsible for generating the vertical outline of a model from G-code
*
*       Process:
*       Takes in G-code, read line-by-line, recognize if receiving arc code 
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

#include <iostream>
#include <fstream>
#include <string>   
#include <opencv2/plot.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;
class model
{

public:

	model();

/*
* readGcode: reads Gcode and stores the values from a specific axis into an array
* which then stores the min/max of each layer into arrays (or a single 2D array)
* that are returned
*/
void readGcode(string gcode);

/*
* plotGcode: takes two arrays (or a single 2D array) and outputs (or stores) an 
* image of those points which then stores the min/max of each layer into arrays 
* that are returned
*/
void plotGcode();

cv::Mat getMat();

private:
    size_t stt, end, rpdMov, Mov, Y_, Z_, relPos, space;
    int fd = 0; 
    int *i,*j,*arX,*arY;
    int j_ = 0;
    int i_ = 0;
    int lp = 0;
    string valY,valZ;
    cv::Mat xData, yData, display;
    Ptr<plot::Plot2d> plot; //create plot object
};

