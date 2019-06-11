/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 9 de jun de 2019
 *
 */

#ifndef SRC_LIB_SQUAREMATRIX_CPP_
#define SRC_LIB_SQUAREMATRIX_CPP_

#include <cmath>
#include <cstdarg>
#include <typeinfo>

template<typename TYPE, unsigned int DIMENSIONS, unsigned int ELEMENTS_PER_DIMENSION>
/**
 * Creates a linear matrix 1d
 * Creates a square matrix 2d
 * Creates a cubic matrix 3d
 * And so on... stored on linear array.
 * Why? Because its faster and easier to manage!
 */
class SquareMatrix {
	private:

		/**
		 * The data container
		 */
		TYPE* arrData = new TYPE[DIMENSIONS * ELEMENTS_PER_DIMENSION];

		void (*uninitializationFunction)(TYPE& data);

		/**
		 * Calculates the actual position
		 * related to the given coordinates
		 * @param coordinates
		 */
		long calculateLinearCoordinate(va_list coordinates) {

			long coord = 0;

			for (int dimIndex = DIMENSIONS - 1; dimIndex >= 0; dimIndex--) {
				long co = va_arg(coordinates, long);
				long ex = pow(ELEMENTS_PER_DIMENSION, dimIndex);
				coord += ex * co;
			}

			return coord;
		}
	public:

		/**
		 * Length per dimension
		 */
		const unsigned int length = ELEMENTS_PER_DIMENSION;

		/**
		 * Amount of dimensions
		 */
		const unsigned int dimensions = DIMENSIONS;

		// TODO specify the dimensions in constructor using va_list
		SquareMatrix(TYPE (*initializationFunction)(), void (*uninitializationFunction)(TYPE& data) = nullptr) {
			this->uninitializationFunction = uninitializationFunction;

			for (unsigned int i = 0; i < DIMENSIONS * ELEMENTS_PER_DIMENSION; i++) {
				this->arrData[i] = (*initializationFunction)();
			}
		}

		~SquareMatrix() {

			if (this->uninitializationFunction != nullptr) {
				for (unsigned int i = 0; i < DIMENSIONS * ELEMENTS_PER_DIMENSION; i++) {
					(*uninitializationFunction)(this->arrData[i]);
				}
			}

			delete[] this->arrData;
		}

		/**
		 * Sets an element in to the matrix
		 * @param value
		 * @param coordinates
		 * @return true = success, false = fail
		 */
		bool set(TYPE value, ...) {
			va_list coordinates;
			va_start(coordinates, DIMENSIONS);
			long linearCoord = this->calculateLinearCoordinate(coordinates);
			va_end(coordinates);

			if (linearCoord > DIMENSIONS * ELEMENTS_PER_DIMENSION) {
				return false;
			}

			this->arrData[linearCoord] = value;
			return true;
		}

		/**
		 * Returns values given the indexes
		 * @return
		 */
		TYPE get(...) {
			va_list coordinates;
			va_start(coordinates, DIMENSIONS);
			long linearCoord = this->calculateLinearCoordinate(coordinates);
			va_end(coordinates);
			return this->arrData[linearCoord];
		}
};

#endif /* SRC_LIB_SQUAREMATRIX_CPP_ */
