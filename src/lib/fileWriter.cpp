/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Contains all variables and functions use it to write the data files
 */
#include <bits/types/FILE.h>
#include <cstdio>

static FILE* filewriter;
static char alreadyOpen = 0;

/**
 * Open a file for writing
 * @param filePath
 */
void openFile(const char* filePath) {

	if (alreadyOpen) return;

	filewriter = fopen(filePath, "w");
	alreadyOpen = 1;
}

/**
 * Write some numeric data into the opened file
 * @param value
 */
void writeNumberToFile(double value) {
	fprintf(filewriter, "%lf\n", value);
}

/**
 * Write some char data into the opened file
 * @param value
 */
void writeCharsToFile(const char* value) {
	fprintf(filewriter, "%s", value);
}

/**
 * Closes de file
 */
void closeFile() {
	fclose(filewriter);
	alreadyOpen = 0;
}
