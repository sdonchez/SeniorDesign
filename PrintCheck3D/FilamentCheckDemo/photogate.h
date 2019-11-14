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
#include <stdio.h>
#include <wiringPi.h>
class photogate{
public:
	photogate(int pin = 9);
	
	/*********************************************************************
	*	filamentCheck: This method connects the Raspberry Pi to the
	*		photogate and pauses the print if it detects no filament.
	*********************************************************************/
	bool filamentCheck();

private:
	int pin;
};