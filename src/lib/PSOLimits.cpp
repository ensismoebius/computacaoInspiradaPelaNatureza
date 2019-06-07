/*
 * PSOLimits.h
 *
 *  Created on: 6 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_LIB_PSOLIMITS_CPP_
#define SRC_LIB_PSOLIMITS_CPP_

#include <cmath>
#include <iostream>

class PSOLimits {
	private:
		int amountOfLimits;
		int amountOfSetedLimits;

	public:
		double* coordLimits;

		PSOLimits(unsigned int amountOfDimensions) {
			this->amountOfSetedLimits = -1;
			this->amountOfLimits = amountOfDimensions * 2;
			this->coordLimits = new double[this->amountOfLimits];

			// default for limits: No limits!!!
			for (int li = 0; li < this->amountOfLimits; li++) {
				this->coordLimits[li] = std::numeric_limits<double>::max() * pow(-1, li);
			}
		}

		~PSOLimits() {
			delete[] this->coordLimits;
		}

		void addLimits(double lowerLimit, double upperLimit) {

			// checks if there is enough space to put the limits
			if (this->amountOfSetedLimits + 2 == this->amountOfLimits) {
				std::cout << "Max of limits reached" << std::endl;
				exit(1);
				return;
			}

			// checks if upperLimit is bigger than lowerLimit
			if (upperLimit < lowerLimit) {
				std::cout << "upperLimit must be bigger than lowerLimit" << std::endl;
				exit(1);
				return;
			}

			this->amountOfSetedLimits++;
			this->coordLimits[this->amountOfSetedLimits] = upperLimit;
			this->amountOfSetedLimits++;
			this->coordLimits[this->amountOfSetedLimits] = lowerLimit;
		}

};

#endif /* SRC_LIB_PSOLIMITS_CPP_ */
