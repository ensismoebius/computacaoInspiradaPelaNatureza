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
		/**
		 * Best fitness value
		 */
		inline static double bestValue;

		/**
		 * Best coordinates
		 */
		inline static double* bestCoordnates;

		/**
		 * Fitness function
		 * @param the fitness function
		 * @return fitness value (the lower the better)
		 */
		inline static double (*fitnessFunction)(double*, unsigned int);

		unsigned int coordSize;

		double currentValue;
		double* currentCoords;

		double myOptimalValue;
		double* myOptimalCoords;

		double velocity;

		Habitant** neighbors;

		// Constructor definition
		Habitant(unsigned int amountOfDimensions, Habitant** neighbors, double (*fitnessFunction)(double*, unsigned int)) {

			this->coordSize = amountOfDimensions;
			this->velocity = getUniformDistributedRandomPertubation();

			this->neighbors = neighbors;
			this->currentCoords = new double[amountOfDimensions];
			this->myOptimalCoords = new double[amountOfDimensions];

			// dn stands for "dimension number"
			for (unsigned int dn = 0; dn < amountOfDimensions; dn++) {
				this->myOptimalCoords[dn] = this->currentCoords[dn] = getUniformDistributedRandomPertubation();
			}

			if (bestCoordnates == 0) {
				Habitant::bestCoordnates = new double[amountOfDimensions];
				Habitant::bestValue = std::numeric_limits<double>::max();
				Habitant::fitnessFunction = fitnessFunction;
			}

			this->currentValue = this->evaluate(this->currentCoords, this->coordSize);
		}

		double evaluate(double* coords, unsigned int coordsSize) {

			double value = (*this->fitnessFunction)(coords, coordsSize);

			if (value < bestValue) {
				bestValue = value;

				for (unsigned int i = 0; i < this->coordSize; i++) {
					bestCoordnates[i] = coords[i];
				}
			}

			if (value < this->myOptimalValue) {
				this->myOptimalValue = value;

				for (unsigned int i = 0; i < this->coordSize; i++) {
					this->myOptimalCoords[i] = coords[i];
				}
			}

			return value;
		}
};
