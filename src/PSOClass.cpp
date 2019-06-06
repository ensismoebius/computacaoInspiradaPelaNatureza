/*
 * PSO.h
 *
 *  Created on: 30 de mai de 2019
 *      Author: ensis
 */
#include "Habitant.cpp"
class PSO {
	public:
		Habitant*** swarms;

		double minSpeed = -2;
		double maxSpeed = 2;

		unsigned int amountOfSwarms = 1;
		unsigned int maxIterations = 100;
		unsigned int amountOfDimensions = 1;
		unsigned int amountOfPopulationPerSwarm = 4;

		PSO() {

			swarms = new Habitant**[amountOfSwarms];

			// si stands for Swarm Index
			// pi stands for Point Index
			for (unsigned int si = 0; si < amountOfSwarms; si++) {

				swarms[si] = new Habitant*[amountOfPopulationPerSwarm];

				for (unsigned int pi; pi < amountOfPopulationPerSwarm; pi++) {

					unsigned int* neighborIndex = generateNeighborhood(amountOfPopulationPerSwarm, pi);

					swarms[si][pi] = new Habitant(amountOfDimensions, minSpeed, maxSpeed, swarms[si], neighborIndex, fitnessFunction);
				}
			}
		}

		static double fitnessFunction(double* values, unsigned int valuesSize) {
			return values[valuesSize - 1] * values[valuesSize - 1];
		}

		static unsigned int* generateNeighborhood(unsigned int amountOfPopulation, unsigned int pointIndex) {

			unsigned int middleIndex = amountOfPopulation / 2;
			unsigned int* indexes = new unsigned int[middleIndex];

			for (unsigned int i = 0; i < middleIndex; i++) {

				if (i % 2 == 0) {
					indexes[i] = (pointIndex + middleIndex + 1) % amountOfPopulation;
					continue;
				}

				indexes[i] = (pointIndex + middleIndex - 1) % amountOfPopulation;
			}

			return indexes;
		}

		void simulate(unsigned int maxIterations) {

			// i stands for iterations
			for (unsigned int i = 0; i < maxIterations; i++) {

				// si stands for Swarm Index
				for (unsigned int si; si < amountOfSwarms; si++) {

					// pi stands for Point Index
					for (unsigned int pi; pi < amountOfSwarms; pi++) {
						swarms[si][pi]->evaluate();
					}
				}
			}
		}
};
