#include "RAMBoInterface.h"
#include "photogate.h"
#include "print3d.h"

int main() {
	RAMBoInterface printer = RAMBoInterface("COM1", 115200);
	photogate myphotogate = photogate(7);
	print3d currentPrint = print3d(printer, myphotogate);

	currentPrint.monitorPrint();
	return 0;
}