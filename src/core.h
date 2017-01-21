#ifndef CORE_H
#define CORE_H

void handleFile(FILE *fileCache);
void read(const char *filename);
void setupOptReg(const char *flag);
void printEmptyBin(unsigned char len);

char const gHelp[] =
"  https://github.com/but0n/xd\n"
"\n"
"  Usage: xd <options> <infile>\n"
"\n"
"  Options:\n"
"\n"
"      -c               : turn colorization on always\n"
"      -l len           : stop after <len> octets.\n"
"\n"
"      -h               : Displays this usage screen\n"
"";

unsigned short gOptRegister = 0;	// Default Options

#define FLAG_HELP			'h'
#define FLAG_COLOR			'c'
#define FLAG_LENGTH			'l'

#define ENABLE_COLOR		0b0000000000000001
#define ENABLE_USAGE		0b0000000000000010
#define ENABLE_STOP			0b0000000000000100
#define LEN					0b1111111111111000
#define LEN_OFFSET			3

#define GET_LEN()			(gOptRegister & LEN)>>LEN_OFFSET
#define ISENABLE(opt)		gOptRegister & (opt)

#define PRINTCOLOR(color)	{\
	if(ISENABLE(COLORENABLE))\
		printf(color);\
}


#endif
