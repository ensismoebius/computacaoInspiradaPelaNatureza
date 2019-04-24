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
#include <stddef.h>
#include <cmath>
#include <iostream>

/**
 * Thanks to:
 * @author Kaustav kumar Chanda
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 */
typedef union {

		float f;
		struct {

				// Order is important.
				// Here the members of the union data structure
				// use the same memory (32 bits).
				// The ordering is taken
				// from the LSB to the MSB.
				unsigned int mantissa :23;
				unsigned int exponent :8;
				unsigned int sign :1;

		} raw;
} myfloat;

/*
 * variableSizes.cpp
 *
 *  Created on: 14 de abr de 2019
 *      Author: ensis
 */
void showVariableSizes() {
	std::cout << "Size of char : " << sizeof(char) << std::endl;
	std::cout << "Size of int : " << sizeof(int) << std::endl;
	std::cout << "Size of short int : " << sizeof(short int) << std::endl;
	std::cout << "Size of long int : " << sizeof(long int) << std::endl;
	std::cout << "Size of float : " << sizeof(float) << std::endl;
	std::cout << "Size of double : " << sizeof(double) << std::endl;
	std::cout << "Size of wchar_t : " << sizeof(wchar_t) << std::endl;
}

/**
 * Thanks to:
 * @author Kaustav kumar Chanda
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 */
char* ieeePartToCharArray(int n, int i) {

	char* res = new char[i];

	int k;
	for (k = i - 1; k >= 0; k--) {

		if ((n >> k) & 1) {
			res[i - 1 - k] = 1;
		} else {
			res[i - 1 - k] = 0;
		}
	}

	return res;
}

/**
 * Thanks to:
 * @author Kaustav kumar Chanda
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 */
unsigned int charArrayToIeeePart(char* arr, unsigned int low, unsigned int high) {
	unsigned int f = 0, i;
	for (i = high; i >= low; i--) {
		f = f + arr[i] * pow(2, high - i);
	}
	return f;
}

/**
 * Thanks to:
 * @author Kaustav kumar Chanda
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 */
char* convertFloatToIEEE754BinaryArray(float value) {

	char* res = new char[32];

	// Instantiate the union
	myfloat var;

	// Get the real value
	var.f = value;

	// Prints the IEEE 754 representation
	// of a float value (32 bits)

	res[0] = (ieeePartToCharArray(var.raw.sign, 1))[0];

	char* expo = ieeePartToCharArray(var.raw.exponent, 8);
	for (int i = 0; i < 8; i++) {
		res[i + 1] = expo[i];
	}

	char* mantissa = ieeePartToCharArray(var.raw.mantissa, 23);
	for (int i = 0; i < 23; i++) {
		res[i + 9] = mantissa[i];
	}

	delete[] expo;
	delete[] mantissa;

	expo = NULL;
	mantissa = NULL;

	return res;
}

/**
 * Thanks to:
 * @author Kaustav kumar Chanda
 * @url https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
 */
float convertIEEE754BinaryArrayToFloat(char* ieee) {
	myfloat var;

	// Convert the least significant
	// mantissa part (23 bits)
	// to corresponding decimal integer
	unsigned int f = charArrayToIeeePart(ieee, 9, 31);

	// Assign integer representation of mantissa
	var.raw.mantissa = f;

	// Convert the exponent part (8 bits)
	// to a corresponding decimal integer
	f = charArrayToIeeePart(ieee, 1, 8);

	// Assign integer representation
	// of the exponent
	var.raw.exponent = f;

	// Assign sign bit
	var.raw.sign = ieee[0];

	return var.f;
}
