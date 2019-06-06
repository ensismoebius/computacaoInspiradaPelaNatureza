/*
 * PSO.h
 *
 *  Created on: 30 de mai de 2019
 *      Author: ensis
 */
#include "PSONeighborhood.cpp"
#include "PSOParticle.cpp"
#include "PSOLimits.cpp"

#include <iostream>

#ifndef SRC_LIB_PSO_CPP_
#define SRC_LIB_PSO_CPP_

class PSO {
	public:
		PSOParticle** swarm;

		int amountOfDimensions;
		unsigned int amountOfPopulation;

		PSO(double (*fitnessFunction)(double*, unsigned int), unsigned int amountOfPopulation, int amountOfDimensions, double minSpeed, double maxSpeed, double selfConfidence, double groupConfidence, PSOLimits* limits) {

			this->amountOfPopulation = amountOfPopulation;
			this->amountOfDimensions = amountOfDimensions;

			swarm = new PSOParticle*[this->amountOfPopulation];

			// Creates the points and its respective neighborhoods
			for (unsigned int pi = 0; pi < this->amountOfPopulation; pi++) {
				PSONeighborhood* neighborhood = new PSONeighborhood(this->amountOfPopulation, this->amountOfDimensions, pi);
				this->swarm[pi] = new PSOParticle(this->amountOfDimensions, minSpeed, maxSpeed, selfConfidence, groupConfidence, this->swarm, neighborhood, limits, fitnessFunction);
			}
		}

		void simulate(unsigned int maxIterations, void (*printFunction)(double, double*, double, double*)) {

			// i stands for Iterations
			for (unsigned int i = 0; i < maxIterations; i++) {

				// updates a static field for all members of population
				swarm[0]->generateFi();

				// pi stands for Point Index
				for (unsigned int pi = 0; pi < amountOfPopulation; pi++) {
					swarm[pi]->evaluate();
					swarm[pi]->updateSpeed();
					swarm[pi]->updateLocation();
					(*printFunction)(swarm[pi]->neighborhood->bestNeighborValue, swarm[pi]->neighborhood->bestNeighborCoordinates, swarm[pi]->fitnessValue, swarm[pi]->currentCoords);
				}
			}
		}
};
#endif /* SRC_LIB_PSO_CPP_ */
