#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "tkusb.h"

int main()
{
	unsigned char data[8];
	memset(data, 0xff, 8);
	printf("Tokuden Spartan-6 board firmware eraser\n");
	printf("========================================================================\n");
	printf("Warning:This software erase EZ-USB FX2 firmware EEPROM of TKDN-SP6-Board\n");
	printf("警告:このソフトを起動すると、ボード上のUSBファームウェアが消去されます\n");
	printf("========================================================================\n");
	printf("Erase EEPROM OK? (y/n) ");
	if (_getch() != 'y') return 0;
	printf("\n");

	if (USBOpen() == false) {
		printf("TKDN-SP6-BRD not found.");
		return 0;
	}

	USBUnlockEEPROMFirmArea("REWRITE");
	if (USBWriteEEPROM(0, data, 8))
	{
		printf("Erase success.\n");
	}
	else
	{
		printf("Erase Failed.\n");
	}
	USBClose();

	return 0;
}
