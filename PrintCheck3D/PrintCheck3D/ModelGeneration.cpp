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

/*
* readGcode: reads Gcode and stores the values from a specific axis into an array
* which then stores the min/max of each layer into arrays (or a single 2D array)
* that are returned
*/
void ModelGeneration::readGcode(string gcode) //read the Y/Z axis
{
  stt = gcode.find(";LAYER:0"); 
  end = gcode.find("M140 S0");
  rpdMov = gcode.find("G0");
  Mov = gcode.find("G1");
  relPos = gcode.find("G91"); //NOT GOOD TO HAVE!! to do: if this is found, spit ERROR
  


  if(stt != string::npos){                   //detect when data collection must start
        lp = 1;
  }
  
  if(lp == 1){
    
    if(end != string::npos){                 //detect when data collection must end
        lp = 0;
        break;
    }
    if(rpdMov != string::npos){
        Y_ = gcode.find('Y');
        Z_ = gcode.find('Z');

        if(Y_ != string::npos){ //finds where "Y" is present
            space = gcode.find(' ',Y_);      //finds the closest space near "Y"
            for(int k = Y_+1,k < space,k++){ //grabs the char of the numbers between Y and the next space
                valY += string.at(k);         //concatenates each char to create a single int
            }
            arrX[*i] = (int)valY;             //turns the string of char into an int
            *i++;
        }

        if(Z_ != string::npos){ //finds where "Z" is present
            space = gcode.find(' ',Z_);      //finds the closest space near "Z"
            for(int k = Z_+1,k < space,k++){ //grabs the char of the numbers between "Z" and the next space
                valZ += string.at(k);         //concatenates each char to create a single int
            }
            arrY[*j] = (int)valZ;             //turns the string of char into an int and-
            *j++;                             //-stores into the array to plot
        }
   
    }
    if(Mov != string::npos){
        Y_ = gcode.find('Y');

        if(Y_ != string::npos){ //finds where "Y" is present
            space = gcode.find(' ',Y_);      //finds the closest space near "Y"
            for(int k = Y_+1,k < space,k++){ //grabs the char of the numbers between Y and the next space
                valY += string.at(k);         //concatenates each char to create a single int
            }
            arrX[*i] = (int)valY;             //turns the string of char into an int
            *i++;
        }
      }
    }
}
 


/*
* plotGcode: takes two arrays (or a single 2D array) and outputs (or stores) an 
* image of those pointswhich then stores the min/max of each layer into arrays 
* that are returned
*/
void ModelGeneration::plotGcode(int arrX[],int arrY[])
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
    imwrite("outline.jpg", display); //write image to outline file   

}


