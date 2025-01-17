#pragma once

/*******************************************************************************
* This file is part of PrintCheck3D
* Copyright(C) 2019 Stephen Donchez, Jared Rymsza, Robert Pink
*
* This program is free software : you can redistribute itand /or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.If not, see < https://www.gnu.org/licenses/>.
*******************************************************************************/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class gCodeTransfer {
public:
	gCodeTransfer(char* inFile);

	~gCodeTransfer();

	std::vector<std::string> getVector();

private:
	std::vector<std::string> fileByLine;
};