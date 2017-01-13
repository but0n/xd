#include <stdio.h>
#include <stdlib.h>

int ReverseInt(int i) {
	unsigned char *split = (unsigned char*)&i;
	return ((int)split[0])<<24 | split[1]<<16 | split[2]<<8 | split[3];
}

void readPNG(const char *filename) {
	printf("File name: %s\n", filename);
	FILE *fp = NULL;
	if ((fp = fopen(filename, "rb")) == NULL)
		printf("Failed\n");
	else {
		printf("Reading...\n");
		int magic_number = 0;
		int number = 0;
		fread((char*)&magic_number, sizeof(magic_number), 1, fp);
		magic_number = ReverseInt(magic_number);
		printf("Magic number:\t0x%08x\n", magic_number);
		fread((char*)&number, sizeof(number), 1, fp);
		number = ReverseInt(number);
		printf("Number:\t0x%08x\n", number);
	}
	fp = NULL;
	fclose(fp);
}


int main() {
	readPNG("logo.png");
	printf("return from main funciton\n");
	return 0;
}
