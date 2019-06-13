/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 10 de jun de 2019
 *
 */

#ifndef SRC_LIB_ACOANT_CPP_
#define SRC_LIB_ACOANT_CPP_

#include <map>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "geometry.h"
#include "ACOPoint.cpp"
#include "gaussianRandom.h"

class Ant {
	public:
		ACOPoint* startingPoint;
		unsigned int amountOfPoints;

		inline static double alpha;
		inline static double betha;
		inline static double deltaWeight;

		std::map<long, bool> visitedPoints;

		Ant(ACOPoint* startingPoint, unsigned int amountOfPoints, double alpha = 1, double betha = 5, double deltaWeight = 0.5) {
			Ant::alpha = alpha;
			Ant::betha = betha;
			Ant::deltaWeight = deltaWeight;

			this->startingPoint = startingPoint;
			this->amountOfPoints = amountOfPoints;
		}

		void walk() {
			// The ant forgets his path just before each walk
			resetVisited();

			// Do the walk
			this->walk(0, this->startingPoint, this->startingPoint, true);
		}

	private:

		void walk(ACOPoint* ancestor, ACOPoint* start, ACOPoint* end, bool ignoreFirst = false) {

			if (start == end && !ignoreFirst) return;

			ACOPoint* next = 0;
			while (next == 0) {
				next = this->getNextPoint(ancestor, start);
				if (next == 0 && isAllPointsVisited()) {
					next = end;
				}
			}

			walk(start, next, end);
			this->gotoToPoint(start, next);
		}

		void gotoToPoint(ACOPoint* from, ACOPoint* to) {
			double newWeight = 1 / euclidianDistance2d(from->coordinates.data(), to->coordinates.data());
			newWeight = (1 - Ant::deltaWeight) * from->connectionsWeights[to->index] + newWeight;

			ACOPoint::setWeightBeetwen(from, to, newWeight);
		}
		void resetVisited() {
			this->visitedPoints.clear();
		}
		ACOPoint* getNextPoint(ACOPoint* ancestor, ACOPoint* current) {

			ACOPoint* bestPoint = 0;

			double weight = 0;
			double distance = 0;
			double totalSum = 0;

			double randomValue = 0;
			double probability = 0;

			// Mark current as visited by this ant;
			this->visitedPoints[current->index] = true;

			// Mark the ancestor as visited (if any)
			if (ancestor != 0) {
				this->visitedPoints[ancestor->index] = true;
			}

			// Calculate the total sum for probability
			for (unsigned int i = 0; i < current->connections.size(); i++) {

				//ignore visited connections
				if (this->visitedPoints[current->connections[i]->index]) continue;

				// Retrieves the weight

				long rrr = current->connections[i]->index;
				weight = current->connectionsWeights[rrr];
				weight = pow(weight, alpha);

				// Retrieves the inverse of distance
				distance = euclidianDistance2d(current->coordinates.data(), current->connections[i]->coordinates.data());
				distance = 1 / distance;
				distance = pow(distance, betha);

				totalSum += weight * distance;
			}

			// Calculate the probabilities
			for (unsigned int i = 0; i < current->connections.size(); i++) {

				//ignore visited connections
				if (this->visitedPoints[current->connections[i]->index]) continue;

				// Probability of weight
				weight = current->connectionsWeights[current->connections[i]->index];
				weight = pow(weight, alpha);

				// Probability of distance
				distance = euclidianDistance2d(current->coordinates.data(), current->connections[i]->coordinates.data());
				distance = 1 / distance;
				distance = pow(distance, betha);

				// Calculate the overall probability
				probability = (weight * distance) / totalSum;

				// Generates a random number against which
				// the overall probability will be compared
				randomValue = getUniformDistributedRandomPertubation() / (double) RAND_MAX;

				// Checks the best point probability
				if (probability >= randomValue) {
					bestPoint = current->connections[i];
				}
			}
			return bestPoint;
		}
		bool isAllPointsVisited() {

			if (this->visitedPoints.size() < this->amountOfPoints) return false;

			for (unsigned int i = 0; i < this->visitedPoints.size(); i++) {
				if (!this->visitedPoints[i]) return false;
			}

			return true;
		}
};

#endif /* SRC_LIB_ACOANT_CPP_ */
