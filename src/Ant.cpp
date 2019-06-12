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
#include "lib/geometry.h"
#include "lib/gaussianRandom.h"
class Ant {
	public:
		Point* startingPoint;

		inline static double alpha;
		inline static double betha;
		inline static double deltaWeight;

		Ant(Point* startingPoint, double alpha = 1, double betha = 5, double deltaWeight = 0.5) {
			Ant::alpha = alpha;
			Ant::betha = betha;
			Ant::deltaWeight = deltaWeight;

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
			this->gotoToPoint(start, next);
		}

		void gotoToPoint(Point* from, Point* to) {
			double delta = 1 / euclidianDistance2d(from->coordinates.data(), to->coordinates.data());
			delta = (1 - Ant::deltaWeight) * from->connectionsWeights[to->index] + delta;

			Point::setWeightBeetwen(from, to, delta);
		}

		Point* getNextPoint(Point* ancestor, Point* current) {

			Point* bestPoint = 0;

			double weight = 0;
			double distance = 0;

			double rnd = 0;

			double weightValue = 0;
			double distanceValue = 0;
			double totalSum = 0;

			for (unsigned int i = 0; i < current->connections.size(); i++) {
				// ignore back connections
				if (current->connections[i] == ancestor) continue;

				weightValue = current->connectionsWeights[current->connections[i]->index];
				weightValue = pow(weightValue, alpha);

				distanceValue = euclidianDistance2d(current->coordinates.data(), current->connections[i]->coordinates.data());
				distanceValue = pow(distanceValue, betha);

				totalSum += weightValue * distanceValue;
			}

			for (unsigned int i = 0; i < current->connections.size(); i++) {

				// ignore back connections
				if (current->connections[i] == ancestor) continue;

				// Probability of weight
				weight = current->connectionsWeights[current->connections[i]->index] / weightValue;
				weight = pow(weight, alpha);

				// Probability of distance
				distance = euclidianDistance2d(current->coordinates.data(), current->connections[i]->coordinates.data()) / distanceValue;
				distance = 1 / distance;
				distance = pow(distance, betha);

				double prob = (weight * distance) / totalSum;

				// adds a random component to the choice
				rnd = getUniformDistributedRandomPertubation() / (double) RAND_MAX;

				if (prob >= rnd) {
					bestPoint = current->connections[i];
				}
			}
			return bestPoint;
		}
};

#endif /* SRC_ANT_CPP_ */
