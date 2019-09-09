#pragma once

/*
*	RAMBoInterface.h:
*		Facilitates the creation and use of an interface between the Raspberry
*		Pi hosting the PrintCheck3D application and the RAMBo that controls the
*		printer.
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
#include <iostream>
#include <fstream>
class RAMBoInterface
{

/*
* GCODE Commands Implemented:
* M0:	Unconditional stop. Wait for user to press a button on the LCD (Only if
*		ULTRA_LCD is enabled)
* M24:	Start/resume SD print
* M25:	Pause SD print
*/

public:
/*
* RAMBoInterface: sets up the serial connection between the Raspberry Pi running
*	this application and the RAMBo controlling the printer. First collects
*	desired parameters (or uses defaults if none provided), then attempts to
*	open the serial connection using these parameters. In the event of failure,
*	returns the error condition.
*/
	RAMBoInterface(char* port, int baud);

/*
* ~RAMBoInterface: tears down the serial connection between the Raspberry Pi
*	running this application and the RAMBo controlling the printer. First
*	flushes any remaining data in the serial file descriptor, then closes the
*	port.
*/
	~RAMBoInterface();

/*
* stopPrint: Sends a "M0" GCODE command to the RAMBo, instructing the printer to
*	immediately execute an unconditional stop. Used in the event of print
*	print failure not caused by end of filament
*/
	void stopPrint();

/*
* pausePrint: Sends a "M25" GCODE command to the RAMBo, instructing the printer
*	to pause the printing operation, with the intention of allowing the user to 
*	replace the empty filament supply and resume print operation without loss of
*	progress
*/
	void pausePrint();

/*
* resumePrint: Sends a "M24" GCODE command to the RAMBo, instructing the printer
*	to resume the printing operation, presumably after the empty filament supply
*	has been replaced.
*/
	void resumePrint();

/* fetchGCode: initates a serial transfer of the GCode data for the currently
*	selected file from the RAMBo's SD Card to the Raspberry Pi, for use by the
*	modeling routines in the PrintCheck3D application
*/
	//TODO: Define GCode Retrevial Mechanism

private:
	char* port;
	int portFD;
	int baud;
	
	
};

