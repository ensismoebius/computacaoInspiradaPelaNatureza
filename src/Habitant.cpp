/*
 * Point.h
 *
 *  Created on: 29 de mai de 2019
 *      Author: ensis
 */

#include <limits>
#include "lib/gaussianRandom.h"

class Habitant {
	public:
		inline static double bestValue;
		inline static double* bestCoordnates;

		unsigned int coordSize;

		double currentValue;
		double* currentCoords;

		double myOptimalValue;
		double* myOptimalCoords;

		double mass;
		double velocity;

		Habitant** neighbors;

		// Constructor definition
		Habitant(unsigned int amountOfDimensions, double mass, Habitant** neighbors) {

			this->mass = mass;
			this->velocity = 0;
			this->coordSize = amountOfDimensions;

			this->neighbors = neighbors;
			this->currentCoords = new double[amountOfDimensions];
			this->myOptimalCoords = new double[amountOfDimensions];

			// dn stands for "dimension number"
			for (unsigned int dn = 0; dn < amountOfDimensions; dn++) {
				this->currentCoords[dn] = getUniformDistributedRandomPertubation();
				this->myOptimalCoords[dn] = getUniformDistributedRandomPertubation();
			}

			this->currentValue = this->fitnessFuction(this->currentCoords, this->coordSize);

			bestValue = 0;
		}

		double fitnessFuction(double* coords, unsigned int coordsSize) {
			return coords[coordsSize - 1] * coords[coordsSize - 2];
		}
};
