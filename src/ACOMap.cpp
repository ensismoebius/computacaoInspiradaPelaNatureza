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

		Point** points;
		unsigned int pointsLentgh;

		void resetPointsTags() {
			for (unsigned int i = 0; i < this->pointsLentgh; i++) {

				if (this->points[i] == 0) continue;

				this->points[i]->tag = false;
			}
		}

	public:

		ACOMap(unsigned int neighborhoodSize) {
			this->pointsLentgh = neighborhoodSize;
			this->points = new Point*[neighborhoodSize];
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

				from->addConnection(selectedPoint, 1);
				from->tag = true;
				from = selectedPoint;
				last = selectedPoint;

				checkedPointCounter++;
				selectedPoint = 0;
			}

			last->addConnection(first, 1);
			this->resetPointsTags();
		}

		void printConnections() {
			Point* first = this->points[0];
			Point* p = first;
			p->tag = true;

			long x0 = p->coordinates.at(0);
			long y0 = p->coordinates.at(1);

			long x1;
			long y1;

			unsigned int connectionIndex = 0;

			do {
				std::cout << x0 << "\t" << y0 << "\t";

				connectionIndex = 0;
				do {
					p = p->connections[connectionIndex];
					connectionIndex++;
					if (p == 0) {
						p = first;
						break;
					}
				} while (p->tag);

				p->tag = true;

				x1 = p->coordinates.at(0);
				y1 = p->coordinates.at(1);

				std::cout << x1 - x0 << "\t" << y1 - y0 << "\n";

				x0 = x1;
				y0 = y1;

			} while (p != first);
		}

		double euclidianDistance(int x1, int y1, int x2, int y2) {
			return sqrt(pow(x2 + x1, 2) + pow(y2 + y1, 2));
		}
};

#endif /* SRC_MAP_CPP_ */
