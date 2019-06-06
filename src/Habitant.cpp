/*
 * Point.h
 *
 *  Created on: 29 de mai de 2019
 *      Author: ensis
 */

#include <limits>
#include <random>

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

		Habitant** population;

		unsigned int* neighborsIndexes;

		// Constructor definition
		Habitant(unsigned int amountOfDimensions, double minVel, double maxVel, Habitant** population, unsigned int* neighborsIndexes, double (*fitnessFunction)(double*, unsigned int)) {

			this->coordSize = amountOfDimensions;
			this->velocity = calculateInitialVelocity(minVel, maxVel);

			this->population = population;
			this->neighborsIndexes = neighborsIndexes;
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

		void evaluate() {
			this->currentValue = this->evaluate(this->currentCoords, this->coordSize);
		}

	private:
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

		double calculateInitialVelocity(double minVel, double maxVel) {

			double velocity = minVel + (getUniformDistributedRandomPertubation() / RAND_MAX) * (maxVel - minVel);

			while (velocity < minVel || velocity > maxVel) {
				velocity = minVel + (getUniformDistributedRandomPertubation() / RAND_MAX) * (maxVel - minVel);
			}

			return velocity;
		}
};
