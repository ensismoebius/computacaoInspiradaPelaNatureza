/**
 * @author André Furlan
 * @author Kaustav kumar Chanda
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Utilities to convert values and see another ones
 * a special thanks to Kaustav kumar Chanda, you
 * helped a LOT
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 *
 */

#ifndef SRC_LIB_VARIABLES_H_
#define SRC_LIB_VARIABLES_H_

void showVariableSizes();
float convertIEEE754BinaryArrayToFloat(char* ieee);
char* convertFloatToIEEE754BinaryArray(float value);

#endif /* SRC_LIB_VARIABLES_H_ */
