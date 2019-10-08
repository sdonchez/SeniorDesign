#include "photogate.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	photogate gate = photogate(7);
	bool isObstructed = true;
	bool isObstructedPast;
	cout << "Welcome to the filament detection demo. Press any key to begin, Ctrl-C to exit" << endl;
	getchar();
	while (true) {
		isObstructedPast = isObstructed;
		isObstructed = gate.filamentCheck();
		if (isObstructedPast != isObstructed) {
			if (isObstructed)
				cout << "Filament Detected" << endl;
			else
				cout << "Filament Removed" << endl;
		}
	}
}