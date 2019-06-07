/*
 * Point.h
 *
 *  Created on: 29 de mai de 2019
 *      Author: ensis
 */

#include <random>
#include <limits>

#include "gaussianRandom.h"
#include "PSOLimits.cpp"
#include "PSONeighborhood.cpp"

#ifndef SRC_LIB_PSOPARTICLE_CPP_
#define SRC_LIB_PSOPARTICLE_CPP_

class PSOParticle {
	public:
		inline static PSOLimits* coordLimits;

		inline static double minVel;
		inline static double maxVel;

		inline static double* arrSelfConfidence;
		inline static double* arrGroupConfidence;

		inline static double selfConfidence;
		inline static double groupConfidence;

		/**
		 * Fitness function
		 * @param the fitness function
		 * @return fitness value (the lower the better)
		 */
		inline static double (*fitnessFunction)(double*, unsigned int);

		unsigned int coordSize;

		double fitnessValue;
		double* currentCoords;

		double myBestValue;
		double* myBestCoords;

		double* velocity;

		PSOParticle** population;

		PSONeighborhood* neighborhood;

		// Constructor definition
		PSOParticle(unsigned int amountOfDimensions, double minVel, double maxVel, double selfConfidence, double groupConfidence, PSOParticle** population, PSONeighborhood* neighbors, PSOLimits* limits, double (*fitnessFunction)(double*, unsigned int)) {

			this->myBestValue = std::numeric_limits<double>::max();
			this->coordSize = amountOfDimensions;
			this->neighborhood = neighbors;

			// just executes it if a new set of static values are provided
			if (PSOParticle::coordLimits != limits) {

				PSOParticle::fitnessFunction = fitnessFunction;
				PSOParticle::coordLimits = limits;

				PSOParticle::minVel = minVel;
				PSOParticle::maxVel = maxVel;

				PSOParticle::selfConfidence = selfConfidence;
				PSOParticle::groupConfidence = groupConfidence;

				delete[] PSOParticle::arrSelfConfidence;
				PSOParticle::arrSelfConfidence = new double[this->coordSize];
				delete[] PSOParticle::arrGroupConfidence;
				PSOParticle::arrGroupConfidence = new double[this->coordSize];
			}

			this->velocity = calculateInitialVelocity(minVel, maxVel);

			this->population = population;
			this->currentCoords = new double[this->coordSize];
			this->myBestCoords = new double[this->coordSize];

			// dn stands for "dimension number"
			for (unsigned int dn = 0; dn < this->coordSize; dn++) {
				this->currentCoords[dn] = PSOParticle::coordLimits->coordLimits[dn * 2] * getUniformDistributedRandomPertubation() / (double) RAND_MAX;

				// verify against upper limit
				if (this->currentCoords[dn] > PSOParticle::coordLimits->coordLimits[dn * 2]) {
					this->currentCoords[dn] = PSOParticle::coordLimits->coordLimits[dn * 2];
				}

				// verify against lower limit
				if (this->currentCoords[dn] < PSOParticle::coordLimits->coordLimits[dn * 2 + 1]) {
					this->myBestCoords[dn] = this->currentCoords[dn] = PSOParticle::coordLimits->coordLimits[dn * 2 + 1];
				}
			}

			this->evaluate(this->currentCoords, this->coordSize);
		}

		~PSOParticle() {

			delete this->neighborhood;

			delete[] this->velocity;
			delete[] this->myBestCoords;
			delete[] this->currentCoords;
		}

		void evaluate() {
			this->evaluate(this->currentCoords, this->coordSize);
		}

		void updateSpeed() {
			for (unsigned int i = 0; i < this->coordSize; i++) {
				this->velocity[i] += PSOParticle::arrSelfConfidence[i] * (this->myBestCoords[i] - this->currentCoords[i]) + PSOParticle::arrGroupConfidence[i] * (this->neighborhood->bestNeighborCoordinates[i] - this->currentCoords[i]);

				if (this->velocity[i] > PSOParticle::maxVel) {
					this->velocity[i] = PSOParticle::maxVel;
				}
				if (this->velocity[i] < PSOParticle::minVel) {
					this->velocity[i] = PSOParticle::minVel;
				}
			}
		}

		void updateLocation() {
			for (unsigned int i = 0; i < this->coordSize; i++) {
				this->currentCoords[i] += this->velocity[i];

				if (this->currentCoords[i] > PSOParticle::coordLimits->coordLimits[i]) {
					this->currentCoords[i] = PSOParticle::coordLimits->coordLimits[i];
				}
				if (this->currentCoords[i] < PSOParticle::coordLimits->coordLimits[i + 1]) {
					this->currentCoords[i] = PSOParticle::coordLimits->coordLimits[i + 1];
				}
			}
		}

		void generateFi() {
			for (unsigned int i = 0; i < this->coordSize; i++) {
				PSOParticle::arrSelfConfidence[i] = PSOParticle::selfConfidence * (getUniformDistributedRandomPertubation() / (double) RAND_MAX);
				PSOParticle::arrGroupConfidence[i] = PSOParticle::groupConfidence * (getUniformDistributedRandomPertubation() / (double) RAND_MAX);
			}
		}

	private:

		void evaluate(double* coords, unsigned int coordsSize) {

			this->fitnessValue = (*this->fitnessFunction)(coords, coordsSize);

			// updates the best coordinates and values
			this->neighborhood->setMyValue(this->fitnessValue, coords);

			// updates the habitant best coordinates and values
			if (this->fitnessValue < this->myBestValue) {
				this->myBestValue = this->fitnessValue;

				for (unsigned int i = 0; i < this->coordSize; i++) {
					this->myBestCoords[i] = coords[i];
				}
			}

		}

		double* calculateInitialVelocity(double minVel, double maxVel) {

			double* velocity = new double[this->coordSize];

			for (unsigned int i = 0; i < this->coordSize; i++) {

				velocity[i] = minVel + (getUniformDistributedRandomPertubation() / (double) RAND_MAX) * (maxVel - minVel);

				while (velocity[i] < minVel || velocity[i] > maxVel) {
					velocity[i] = minVel + (getUniformDistributedRandomPertubation() / (double) RAND_MAX) * (maxVel - minVel);
				}
			}

			return velocity;
		}
};
#endif /* SRC_LIB_PSOPARTICLE_CPP_ */
