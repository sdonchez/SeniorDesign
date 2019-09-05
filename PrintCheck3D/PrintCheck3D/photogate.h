#pragma once
/*
*	photogate.h:
*		The photogate class is designed to pause the printer if the
*		photogate detects no filament present in the tube of the printer.
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

#include <wiringSerial.h>
class photogate{
public:
	/*********************************************************************	
	*	gateInterface: This method sets up the serial connection 
	*		between the Raspberry Pi and the photogate component 
	*		of the PrintCheck3D system.
	*
	*********************************************************************/
	gateInterface(char* port, int baud);

	/*********************************************************************
	*	~gateInterface: This method tears down the serial connection 
	*		between the Raspberry Pi and the photogate component 
	*		of the PrintCheck3D system.
	*
	*********************************************************************/
	~gateInterface();
	
	/*********************************************************************
	*	pausePrint: Sends a "M25" GCODE command to the RAMBo, instructing 
	*		the printer to pause the printing operation, with the 
	*		intention of allowing the user to replace the empty filament 
	*		supply and resume print operation without loss of progress.
	*
	*********************************************************************/
	void pausePrint();
	

private:
	char* port;
	int portFD;
	int baud;
}