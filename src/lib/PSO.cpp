/*
 * PSO.h
 *
 *  Created on: 30 de mai de 2019
 *      Author: ensis
 */
#include "PSONeighborhood.cpp"
#include "PSOParticle.cpp"

#include <iostream>
class PSO {
	public:
		PSOParticle** swarm;

		int amountOfDimensions;
		unsigned int amountOfPopulation;

		double* coordLimits;
		int amountOfSetedLimits;

		PSO(double (*fitnessFunction)(double*, unsigned int), unsigned int amountOfPopulation, int amountOfDimensions, double minSpeed, double maxSpeed, double selfConfidence, double groupConfidence) {

			this->amountOfSetedLimits = -1;
			this->amountOfPopulation = amountOfPopulation;
			this->amountOfDimensions = amountOfDimensions;

			swarm = new PSOParticle*[this->amountOfPopulation];

			// default for limits: No limits!!!
			this->coordLimits = new double[this->amountOfDimensions * 2];
			for (int li = 0; li < this->amountOfDimensions * 2; li++) {
				this->coordLimits[li] = std::numeric_limits<double>::max() * pow(-1, li);
			}

			// Creates the points and its respective neighborhoods
			for (unsigned int pi = 0; pi < this->amountOfPopulation; pi++) {
				PSONeighborhood* neighborhood = new PSONeighborhood(this->amountOfPopulation, this->amountOfDimensions, pi);
				this->swarm[pi] = new PSOParticle(this->amountOfDimensions, minSpeed, maxSpeed, selfConfidence, groupConfidence, this->swarm, neighborhood, coordLimits, fitnessFunction);
			}
		}

		void addLimits(double lowerLimit, double upperLimit) {

			if (this->amountOfSetedLimits + 2 == this->amountOfDimensions * 2) {
				std::cout << "Max of limits reached" << std::endl;
				exit(1);
				return;
			}

			this->coordLimits[this->amountOfSetedLimits] = lowerLimit;
			this->amountOfSetedLimits++;
			this->coordLimits[this->amountOfSetedLimits] = upperLimit;
			this->amountOfSetedLimits++;
		}

		void simulate(unsigned int maxIterations, void (*printFunction)(double, double*)) {

			// i stands for Iterations
			for (unsigned int i = 0; i < maxIterations; i++) {

				// updates a static field for all members of population
				swarm[0]->generateFi();

				// pi stands for Point Index
				for (unsigned int pi = 0; pi < amountOfPopulation; pi++) {
					swarm[pi]->evaluate();
					swarm[pi]->updateSpeed();
					swarm[pi]->updateLocation();
					(*printFunction)(swarm[pi]->neighborhood->bestNeighborValue, swarm[pi]->neighborhood->bestNeighborCoordinates);
				}
			}
		}
};
