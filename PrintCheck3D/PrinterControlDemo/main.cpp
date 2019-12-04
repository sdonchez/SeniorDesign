#include <cstdio>
#include "RAMBoInterface.h"
#include "gCodeTransfer.h"
#include <string>

using namespace std;

int main()
{
	RAMBoInterface printer = RAMBoInterface();
	gCodeTransfer printJob = gCodeTransfer("/media/pi/PRINT3D/sample.gcode");
	int choice;
	string menu = "Enter an option from the choices below\n1) insert a filament change\n2) insert a recover\n3) insert a stop\n4) print circle\n5) print gcode\n6) quit";
	while (true) {
		cout << menu << endl;
		int read = scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printer.pausePrint();
			cout << "filament swap initiated" << endl;
			break;
		case 2:
			printer.resumePrint();
			cout << "print resume initiated" << endl;
			break;
		case 3:
			printer.stopPrint();
			cout << "print stop initiated" << endl;
			break;
		case 4:
			printer.printArc();
			cout << "circle print initiated" << endl;
			break;
		case 5:
			printer.runPrintJob(printJob.getVector());
			cout << "printing rocktopus" << endl;
			break;
		case 6:
			return 0;
		default:
			cout << "Your choice is invalid. Please try again" << endl;
		}
	}
}