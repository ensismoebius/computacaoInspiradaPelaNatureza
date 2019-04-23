#include <bits/types/FILE.h>
#include <cstdio>

FILE* filewriter;
char alreadyOpen = 0;

void openFile(const char* filePath) {

	if (alreadyOpen) return;

	filewriter = fopen(filePath, "w");
	alreadyOpen = 1;
}

void writeFile(double value) {
	fprintf(filewriter, "%f\n", value);
}

void closeFile() {
	fclose(filewriter);
	alreadyOpen = 0;
}
