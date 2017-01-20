#include <stdio.h>
#include <stdlib.h>

#define BLANK '.'	// You can custom blank character by redefine here

void handleFile(FILE *fileCache) {
	unsigned char cache;
	unsigned int size = 0;
	char ascii[16] = {};
	while(fread((char*)&cache, sizeof(cache), 1, fileCache)) {
		if (!(size%0x10)) {
			printf("\n%08x: ", size);
		}
		else if (!(size%8)) {
			//	After per 8 bytes insert two space for split
			printf(" ");	// More readable
		}

		// handle Ascii detail area
		if((cache >= '!') && (cache <= '~')) {
			ascii[size%16] = cache;
		} else {
			ascii[size%16] = BLANK;
		}
		// print this byte
		printf("%02x ", cache);
		size++;
		if (!(size%16)) {
			printf("\t%s", ascii);
		}
	}
	printf("\nTotal %d Byte\n", size);
}


void read(const char *filename) {
	printf("File name: %s\n", filename);
	FILE *fp = NULL;
	if ((fp = fopen(filename, "rb")) == NULL)
		printf("Failed\n");
	else {
		handleFile(fp);
	}
	fclose(fp);
	fp = NULL;
}


int main(int argc, char const *argv[]) {
	read("logo.png");
	//	handle arguments
	for(int count = 0; count < argc; count++) {
		//	handle options
		if(argv[count][0] == '-') {
			printf("Command is %s\n", argv[count]);
		}
	}

	printf("return from main funciton\n");
	return 0;
}
