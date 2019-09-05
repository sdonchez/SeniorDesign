/*
*	photogate.cpp:
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

#include "photogate.h"

/*********************************************************************
*	gateInterface: This method sets up the serial connection
*		between the Raspberry Pi and the photogate component
*		of the PrintCheck3D system.
*
*********************************************************************/
photogate::gateInterface(char* port, int baud) {
	this->port = port;
	this->baud = baud;
	try {
		portFD = serialOpen(port, baud);
		if (portFD == -1)
			throw("Error initializing the port");
	}
	catch (char* e) {
		std::cout << e << "error number: " << errno;
	}
}

/*********************************************************************
*	~gateInterface: This method tears down the serial connection
*		between the Raspberry Pi and the photogate component
*		of the PrintCheck3D system.
*
*********************************************************************/
photogate::~photogate()
{
	serialFlush(portFD);
	serialClose(portFD);
}

/*********************************************************************
*	pausePrint: Sends a "M25" GCODE command to the RAMBo, instructing
*		the printer to pause the printing operation, with the
*		intention of allowing the user to replace the empty filament
*		supply and resume print operation without loss of progress.
*
*********************************************************************/
void photogate::pausePrint() {
	char* command = "M25";
	serialPuts(portFD, command);
}