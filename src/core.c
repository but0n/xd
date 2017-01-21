#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "tty.h"

#define BLANK			'.'	// You can custom blank character by redefine here
#define PRINTUSAGE()	{printf("%s\n", gHelp);}

void handleFile(FILE *fileCache) {
	unsigned char cache;
	unsigned int size = 0;
	char ascii[16] = {};
	while(fread((char*)&cache, sizeof(cache), 1, fileCache)) {
		if (!(size%0x10)) {
			PRINTCOLOR(TTY_BLUE);
			printf("\n%08x: ", size);
			PRINTCOLOR(TTY_NONE);
		}
		else if (!(size%8)) {
			//	After per 8 bytes insert two space for split
			printf(" ");	// More readable
		}

		// handle Ascii detail area, store current byte
		ascii[size%16] = ((cache >= '!') && (cache <= '~')) ? cache : BLANK;

		// print current byte
		PRINTCOLOR(TTY_GREEN);
		printf("%02x ", cache);
		PRINTCOLOR(TTY_NONE);

		size++;

		if (!(size%16) || (size == gOptRegister>>LEN_OFFSET)) {
			//	Empty bytes
			printEmptyBin(size%16);
			PRINTCOLOR(TTY_LIGHT_BLUE);
			printf("    %s", ascii);
			PRINTCOLOR(TTY_NONE);
			if (size == gOptRegister>>LEN_OFFSET)
				break;
		}
	}
	printf("\nTotal %d Byte\n", size);
}


void read(const char *filename) {
	printf("File name: %s\n", filename);
	FILE *fp = NULL;
	if ((fp = fopen(filename, "rb")) == NULL)
		printf("Couldn't open this file\n");
	else {
		handleFile(fp);
	}
	fclose(fp);
	fp = NULL;
}

void setupOptReg(const char *flag) {
	while(*++flag) {
		//TODO: Enhancement
		switch (*flag) {
			case FLAG_HELP:
				gOptRegister |= ENABLE_USAGE;
				PRINTUSAGE();
				break;
			case FLAG_COLOR:
				gOptRegister |= ENABLE_COLOR;
				break;
			case FLAG_LENGTH:
				gOptRegister |= ENABLE_STOP;
				break;
			default:
				printf("Error option '%c'\n", *flag);
				break;
		}
	}
}

void printEmptyBin(unsigned char len) {
	if (len) {
		len = 16 - len;
		while(len--) {
			printf("   ");
			if (len==8)
				printf(" ");
		}
	}
}

int main(int argc, char const *argv[]) {
	//	handle arguments
	if (argc == 1) {
		PRINTUSAGE();
		return -1;
	}
	for(int count = 1; count < argc; count++) {
		if(argv[count][0] == '-') {
			// Handle options
			setupOptReg(argv[count]);
			if (ISENABLE(ENABLE_STOP)) {
				gOptRegister |= atoi(argv[count+1]) << LEN_OFFSET;
				count++;
				gOptRegister &= ~ENABLE_STOP;
				//Clean ENABLE_STOP bit after enable
			}
		} else {
			// Handle infile
			read(argv[count]);
		}
	}
	return 0;
}
