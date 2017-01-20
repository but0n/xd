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

		// handle Ascii detail area
		ascii[size%16] = ((cache >= '!') && (cache <= '~')) ? cache : BLANK;

		// print this byte
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
		switch (*flag) {
			case FLAG_HELP:
				gOptRegister |= USAGEENABLE;
				PRINTUSAGE();
				break;
			case FLAG_COLOR:
				gOptRegister |= COLORENABLE;
				break;
			case FLAG_LENGTH:
				gOptRegister |= STOPENABLE;
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
	for(int count = 0; count < argc; count++) {
		//	handle options
		if(argv[count][0] == '-') {
			// Handle options
			setupOptReg(argv[count]);
			if (ISENABLE(STOPENABLE)) {
				gOptRegister |= atoi(argv[count+1]) << LEN_OFFSET;
				count++;
				gOptRegister &= ~STOPENABLE;
				//Clean STOPENABLE bit after enable
			}
		} else {
			// Handle file
			if (count)
				read(argv[count]);
		}
	}
	return 0;
}
