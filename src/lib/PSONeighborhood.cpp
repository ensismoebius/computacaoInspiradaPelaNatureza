/*
 * Neighborhood.c
 *
 *  Created on: 6 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_NEIGHBORHOOD_CPP_
#define SRC_NEIGHBORHOOD_CPP_

#include <limits>

class PSONeighborhood {
	public:
		unsigned int* indexes;
		unsigned int neighborIndexSize;

		double bestNeighborValue;

		double* bestNeighborCoordinates;
		unsigned int bestNeighborCoordinatesSize;

		PSONeighborhood(unsigned int amountOfPopulation, unsigned int amountOfDimensions, unsigned int pointIndex) {

			this->neighborIndexSize = amountOfPopulation / 2;
			this->indexes = new unsigned int[this->neighborIndexSize];

			this->bestNeighborCoordinatesSize = amountOfDimensions;
			this->bestNeighborCoordinates = new double[amountOfDimensions];

			this->bestNeighborValue = std::numeric_limits<double>::max();

			for (unsigned int i = 0; i < this->neighborIndexSize; i++) {

				if (i % 2 == 0) {
					indexes[i] = (pointIndex + this->neighborIndexSize + 1) % amountOfPopulation;
					continue;
				}

				indexes[i] = (pointIndex + this->neighborIndexSize - 1) % amountOfPopulation;
			}
		}

		void setMyValue(double value, double* coordinates) {
			if (value < this->bestNeighborValue) {
				this->bestNeighborValue = value;

				for (unsigned int i = 0; i < this->bestNeighborCoordinatesSize; i++) {
					this->bestNeighborCoordinates[i] = coordinates[i];
				}
			}
		}

};

#endif /* SRC_NEIGHBORHOOD_CPP_ */
