/*
 * Map.h
 *
 *  Created on: 9 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_MAP_CPP_
#define SRC_MAP_CPP_

#include <limits>
#include <cmath>
#include <iostream>
#include "Point.cpp"
class ACOMap {
	private:

		constexpr static double decayRate = 0.1;

		void resetPointsTags() {
			for (unsigned int i = 0; i < this->pointsLentgh; i++) {

				if (this->points[i] == 0) continue;

				this->points[i]->tag = false;
			}
		}
	public:
		Point** points;
		unsigned int pointsLentgh;

		ACOMap(unsigned int neighborhoodSize) {
			this->pointsLentgh = neighborhoodSize;
			this->points = new Point*[neighborhoodSize];

			for (unsigned int i = 0; i < this->pointsLentgh; i++) {
				this->points[i] = 0;
			}
		}

		~ACOMap() {
			for (unsigned int i = 0; i < this->pointsLentgh; i++) {
				delete this->points[i];
			}
			delete[] this->points;
		}

		void addNeighborhood(int x, int y, unsigned int index) {

			if (index >= this->pointsLentgh) {
				std::cout << "There is no such position " << index << " in the list!";
				exit(1);
			}

			this->points[index] = new Point(2, index, x, y);
		}

		void firstSteps() {
			unsigned int checkedPointCounter = 0;

			Point* selectedPoint = 0;
			Point* from = 0;
			Point* to = 0;

			Point* first = 0;
			Point* last = 0;

			double shortestDistance = 0;
			double tempDistance = 0;

			first = from = this->points[0];

			while (checkedPointCounter < this->pointsLentgh) {

				if (from == 0) break;

				tempDistance = 0;
				shortestDistance = std::numeric_limits<double>::max();

				for (unsigned int ni = 0; ni < this->pointsLentgh; ni++) {

					to = this->points[ni];

					// Connects with lower weight
					from->addConnection(to, 0.5);

					if (to == from || to == 0 || to->tag) {
						continue;
					}

					tempDistance = euclidianDistance(from->coordinates[0], from->coordinates[1], to->coordinates[0], to->coordinates[1]);

					if (tempDistance < shortestDistance) {
						shortestDistance = tempDistance;
						selectedPoint = to;
					}
				}

				if (selectedPoint == 0) break;

				Point::setWeightBeetwen(from, selectedPoint, 1);

				//from->addConnection(selectedPoint, 1);
				from->tag = true;
				from = selectedPoint;
				last = selectedPoint;

				checkedPointCounter++;
				selectedPoint = 0;
			}

			last->addConnection(first, 1);
			this->resetPointsTags();
		}

		void decayWeights() {
			for (unsigned int i = 0; i < this->pointsLentgh; i++) {
				for (unsigned int j = 0; j < this->points[i]->connectionsWeights.size(); j++) {
					this->points[i]->connectionsWeights[j] *= (1 - ACOMap::decayRate);
				}
			}
		}

		void printAll() {

			long x1, y1, conx1, cony1;
			conx1 = cony1 = x1 = y1 = 0;

			long x0 = this->points[0]->coordinates.at(0);
			long y0 = this->points[0]->coordinates.at(1);

			for (unsigned int i = 1; i < this->pointsLentgh; i++) {

				if (this->points[i] == 0) continue;

				x1 = this->points[i]->coordinates[0];
				y1 = this->points[i]->coordinates[1];

				std::cout << x0 << "\t" << y0 << "\t";
				std::cout << x1 - x0 << "\t" << y1 - y0 << "\n";

				for (auto& con : this->points[i]->connections) {
					conx1 = con.second->coordinates[0];
					cony1 = con.second->coordinates[1];
					std::cout << x0 << "\t" << y0 << "\t";
					std::cout << conx1 - x0 << "\t" << cony1 - y0 << "\n";
				}

				x0 = x1;
				y0 = y1;
			}
		}

		double euclidianDistance(int x1, int y1, int x2, int y2) {
			return sqrt(pow(x2 + x1, 2) + pow(y2 + y1, 2));
		}
};

#endif /* SRC_MAP_CPP_ */
