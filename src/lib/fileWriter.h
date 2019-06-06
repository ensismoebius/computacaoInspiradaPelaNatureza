/*
 * fileWriter.h
 *
 *  Created on: 22 de abr de 2019
 *      Author: ensis
 */

#ifndef SRC_LIB_FILEWRITER_H_
#define SRC_LIB_FILEWRITER_H_

void closeFile();
void writeNumberToFile(double value);
void writeCharsToFile(const char* value);
void openFile(const char* filePath);
void writeNewlineToFile();
void writeNumberToFileAtSameLine(double value);

#endif /* SRC_LIB_FILEWRITER_H_ */
