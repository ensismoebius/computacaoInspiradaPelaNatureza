/*
 * Point.h
 *
 *  Created on: 10 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_POINT_CPP_
#define SRC_POINT_CPP_

#include <map>
#include <vector>
#include <cstdarg>
#include <stdexcept>
#include <algorithm>

class Point {
	public:
		unsigned int index;
		bool tag = false;
		std::map<unsigned int, double> connectionsWeights;
		std::map<unsigned int, Point*> connections;
		std::vector<long> coordinates;

		Point(unsigned int dimension, unsigned int index, ...) {

			this->index = index;

			va_list coordinates;
			va_start(coordinates, index);

			for (unsigned int i = 0; i < dimension; i++) {
				this->coordinates.push_back(va_arg(coordinates, long));
			}

			va_end(coordinates);
		}

		void addConnection(Point* point, double weight) {

			if (point == 0) return;

			point->connections[this->index] = this;
			point->connectionsWeights[this->index] = weight;

			this->connections[point->index] = point;
			this->connectionsWeights[point->index] = weight;
		}

		static void addWeightBeetwen(Point* one, Point* two, double amount) {
			double weight = one->connectionsWeights[two->index];
			weight += amount;
			setWeightBeetwen(one, two, weight);
		}

		static void setWeightBeetwen(Point* one, Point* two, double weight) {

			if (one->connections[two->index] == 0) {
				one->connections[two->index] = two;
			}

			if (two->connections[one->index] == 0) {
				two->connections[one->index] = one;
			}

			one->connectionsWeights[two->index] = weight;
			two->connectionsWeights[one->index] = weight;
		}
};

#endif /* SRC_POINT_CPP_ */
