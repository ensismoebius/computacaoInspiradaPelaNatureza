/*
 * Ant.h
 *
 *  Created on: 10 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_ANT_CPP_
#define SRC_ANT_CPP_
#include <map>
#include <random>
#include <iostream>
#include "Point.cpp"
#include "lib/geometry.h"
#include "lib/gaussianRandom.h"
class Ant {
	public:
		Point* startingPoint;
		unsigned int amountOfPoints;

		inline static double alpha;
		inline static double betha;
		inline static double deltaWeight;

		std::map<long, bool> visitedPoints;

		Ant(Point* startingPoint, unsigned int amountOfPoints, double alpha = 1, double betha = 5, double deltaWeight = 0.5) {
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

		void walk(Point* ancestor, Point* start, Point* end, bool ignoreFirst = false) {

			if (start == end && !ignoreFirst) return;

			Point* next = 0;
			while (next == 0) {
				next = this->getNextPoint(ancestor, start);
				if (next == 0 && isAllPointsVisited()) {
					next = end;
				}
			}

			walk(start, next, end);
			this->gotoToPoint(start, next);
		}

		void gotoToPoint(Point* from, Point* to) {
			double newWeight = 1 / euclidianDistance2d(from->coordinates.data(), to->coordinates.data());
			newWeight = (1 - Ant::deltaWeight) * from->connectionsWeights[to->index] + newWeight;

			Point::setWeightBeetwen(from, to, newWeight);
		}
		void resetVisited() {
			this->visitedPoints.clear();
		}
		Point* getNextPoint(Point* ancestor, Point* current) {

			Point* bestPoint = 0;

			double weight = 0;
			double distance = 0;
			double totalSum = 0;

			double randoValue = 0;
			double probability = 0;

			// Mark current as visited by this ant;
			this->visitedPoints[current->index] = true;

			// Mark the ancestor as visited (if any)
			if (ancestor != 0) {
				this->visitedPoints[current->index] = true;
			}

			// Calculate the total sum for probability
			for (unsigned int i = 0; i < current->connections.size(); i++) {

				//ignore visited connections
				if (this->visitedPoints[current->connections[i]->index]) continue;

				// Retrieves the weight
				weight = current->connectionsWeights[current->connections[i]->index];
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
				randoValue = getUniformDistributedRandomPertubation() / (double) RAND_MAX;

				// Checks the best point probability
				if (probability >= randoValue) {
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

#endif /* SRC_ANT_CPP_ */
