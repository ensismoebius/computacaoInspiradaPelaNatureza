/*
 * Ant.h
 *
 *  Created on: 10 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_ANT_CPP_
#define SRC_ANT_CPP_
#include <random>
#include <iostream>
#include "Point.cpp"
#include "lib/gaussianRandom.h"
class Ant {
	public:
		Point* startingPoint;
		unsigned int pointsLength;

		constexpr static double deltaWeight = 1;

		Ant(Point* startingPoint, unsigned int pointsLength) {
			this->pointsLength = pointsLength;
			this->startingPoint = startingPoint;
		}

		void walk() {
			this->walk(0, this->startingPoint, this->startingPoint, true);
		}

		void walk(Point* ancestor, Point* start, Point* end, bool ignoreFirst = false) {

			if (start == end && !ignoreFirst) return;

			Point* next = 0;
			while (next == 0) {
				next = this->getNextPoint(ancestor, start);
			}

			walk(start, next, end);
			this->gotoNextPoint(start, next);
		}

		void gotoNextPoint(Point* current, Point* next) {
			Point::addWeightBeetwen(current, next, Ant::deltaWeight);
		}

		Point* getNextPoint(Point* ancestor, Point* current) {

			Point* bestPoint = 0;

			double temp = 0;

			double rnd = 0;

			double prob = 0;
			double weightsSum = 0;

			for (unsigned int i = 0; i < current->connections.size(); i++) {
				// ignore back connections
				if (current->connections[i] == ancestor) continue;

				weightsSum += current->connectionsWeights[current->connections[i]->index];
			}

			for (unsigned int i = 0; i < current->connections.size(); i++) {

				// ignore back connections
				if (current->connections[i] == ancestor) continue;

				temp = current->connectionsWeights[current->connections[i]->index] / weightsSum;

				// adds a random component to the choice
				rnd = getUniformDistributedRandomPertubation() / (double) RAND_MAX;

				if (temp > prob + rnd) {
					prob = temp;
					bestPoint = current->connections[i];
				}
			}
			return bestPoint;
		}
};

#endif /* SRC_ANT_CPP_ */
