/*
 * PSO.h
 *
 *  Created on: 30 de mai de 2019
 *      Author: ensis
 */
#include "Habitant.cpp"
class PSO {
	public:
		PSO() {

			unsigned int amountOfSwarms = 4;
			unsigned int amountOfDimensions = 2;
			unsigned int amountOfPopulationPerSwarm = 20;

			Habitant*** swarms = new Habitant**[amountOfSwarms];

			// si stands for Swarm Index
			// pi stands for Point Index
			for (unsigned int si; si < amountOfSwarms; si++) {

				swarms[si] = new Habitant*[amountOfPopulationPerSwarm];

				for (unsigned int pi; pi < amountOfSwarms; pi++) {
					swarms[si][pi] = new Habitant(amountOfDimensions, swarms[si], fitnessFunction);
				}
			}
		}

		static double fitnessFunction(double* values, unsigned int valuesSize) {
			return values[valuesSize - 1] * values[valuesSize - 2];
		}
};
