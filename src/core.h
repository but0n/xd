#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

void handleFile(FILE *fileCache);
void read(const char *filename);
void setupOptReg(const char *flag);

char const gHelp[] =
"  https://github.com/but0n\n"
// "\n"
"  Usage: xd <options> <infile>\n"
"\n"
"  Options:\n"
"\n"
"      -c               : turn colorization on always\n"
"      -l len           : stop after <len> octets.\n"
"      -n hex           : User specified ANonce when doing the 4-way handshake\n"
"\n"
"  Filter options:\n"
"      --bssid MAC      : BSSID to filter/use\n"
"      --essids file    : read a list of ESSIDs out of that file\n"
"\n"
"      --help           : Displays this usage screen\n"
"\n";

unsigned char gOptRegister = 0;	// Default Options

#define FLAG_HELP			'h'
#define FLAG_COLOR			'c'
#define FLAG_LENGTH			'l'

#define COLORENABLE			0b00000001
#define USAGEENABLE			0b00000010
#define STOPENABLE			0b00000100

#define ISENABLE(opt)		gOptRegister&(opt)

#define PRINTCOLOR(color)	{\
	if(ISENABLE(COLORENABLE))\
		printf(color);\
}


#endif
