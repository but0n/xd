#include <stdio.h>
#include <stdlib.h>


void readImg(const char *filename) {
	FILE *fp = NULL;
	fp = fopen(filename, "rb");
	if (fp==NULL)
		printf("Failed\n");
	fclose(fp);
}


int main() {
	readImg("logo.png");
	printf("Hello\n");
	return 0;
}
