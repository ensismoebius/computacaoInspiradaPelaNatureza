/*
 * Ant.h
 *
 *  Created on: 10 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_ANT_CPP_
#define SRC_ANT_CPP_
#include <iostream>
#include "Point.cpp"
#include "lib/gaussianRandom.h"
class Ant {
	public:
		Point* startingPoint;
		unsigned int pointsLength;

		Point* currentPoint;

		constexpr static double deltaWeight = 0.1;

		Ant(Point* startingPoint, unsigned int pointsLength) {
			this->pointsLength = pointsLength;
			this->startingPoint = startingPoint;
		}

		void walk() {
			this->walk(0, this->startingPoint, this->startingPoint, true);
		}

		void walk(Point* ancestor, Point* start, Point* end, bool ignoreFirst = false) {

			if (start == end && !ignoreFirst) return;

			Point* next = this->getNextPoint(ancestor, start);
			walk(start, next, end);

			this->gotoNextPoint(start, next);

//			do {
//				next = this->getNextPoint(ancestor, current);
//				this->gotoNextPoint(current, next);
//
//				current = next;
//				ancestor = current;
//			} while (current != end);
		}

		void gotoNextPoint(Point* current, Point* next) {
			Point::addWeightBeetwen(current, next, Ant::deltaWeight);
			this->currentPoint = next;
		}

		Point* getNextPoint(Point* ancestor, Point* current) {

			Point* bestPoint = 0;

			double temp = 0;

			double rnd = 0;

			double prob = 0;
			double weightsSum = 0;

			for (auto& p : current->connections) {

				// ignore back connections
				if (p.second == ancestor) continue;

				weightsSum += current->connectionsWeights[p.second->index];
			}

			for (auto& p : current->connections) {

				// ignore back connections
				if (p.second == ancestor) continue;

				temp = current->connectionsWeights[p.second->index] / weightsSum;

				// adds a random component to the choice
				rnd = getUniformDistributedRandomPertubation();

				if (temp > prob + rnd) {
					prob = temp;
					bestPoint = p.second;
				}
			}
			return bestPoint;
		}
};

#endif /* SRC_ANT_CPP_ */
