/*
 * Point.h
 *
 *  Created on: 10 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_POINT_CPP_
#define SRC_POINT_CPP_

#include <vector>
#include <cstdarg>
#include <stdexcept>
#include <algorithm>

class Point {
	private:
		unsigned int index;
		std::vector<double> connectionsWeights;
	public:
		bool tag = false;
		std::vector<Point*> connections;
		std::vector<long> coordinates;

		Point(unsigned int dimension, unsigned int index, ...) {

			this->index = index;

			va_list coordinates;
			va_start(coordinates, dimension);

			for (unsigned int i = 0; i < dimension; i++) {
				this->coordinates.push_back(va_arg(coordinates, long));
			}

			va_end(coordinates);
		}

		void addConnection(Point* point, double weight) {

			if (point == 0) return;

			try {
				point->connections.at(this->index);
			} catch (std::out_of_range& error) {
				point->connections.push_back(this);
				point->connectionsWeights.push_back(weight);
			}

			try {
				this->connections.at(point->index);
			} catch (std::out_of_range& error) {
				this->connections.push_back(point);
				this->connectionsWeights.push_back(weight);
			}
		}

		static void updateWeightBeetwen(Point* one, Point* two, double weight) {

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
