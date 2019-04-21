#include <cmath>
#include <iostream>

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

char* convertFloatToIEEE754BinaryArray(float value) {
	// output
	char* arrIeee754 = new char[32];

	// use reinterpret_cast function
	int *b = reinterpret_cast<int*>(&value);
	// for loop to print out binary pattern
	for (int k = 31; k >= 0; k--) {
		// get the copied bit value shift right k times, then and with a 1.
		arrIeee754[k] = ((*b >> k) & 1);
	}

	return arrIeee754;
}

// C program to convert
// IEEE 754 floating point representation
// into real value

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

// Function to convert a binary array
// to the corresponding integer
unsigned int convertToInt(char* arr, unsigned int low, unsigned int high) {
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
float convertIEEE754BinaryArrayToFloat(char* ieee) {
	myfloat var;

	// Convert the least significant
	// mantissa part (23 bits)
	// to corresponding decimal integer
	unsigned int f = convertToInt(ieee, 9, 31);

	// Assign integer representation of mantissa
	var.raw.mantissa = f;

	// Convert the exponent part (8 bits)
	// to a corresponding decimal integer
	f = convertToInt(ieee, 1, 8);

	// Assign integer representation
	// of the exponent
	var.raw.exponent = f;

	// Assign sign bit
	var.raw.sign = ieee[0];

	return var.f;
}
