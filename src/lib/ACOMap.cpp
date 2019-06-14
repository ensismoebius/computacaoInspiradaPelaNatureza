/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 9 de jun de 2019
 *
 */

#ifndef SRC_LIB_ACOMAP_CPP_
#define SRC_LIB_ACOMAP_CPP_

#include <map>
#include <cmath>
#include <limits>
#include <sstream>
#include <iostream>

#include "geometry.h"
#include "fileWriter.h"
#include "ACOPoint.cpp"
class ACOMap {
	private:
		void resetPointsTags() {
			for (unsigned int i = 0; i < this->pointsLentgh; i++) {

				if (this->points[i] == 0) continue;

				this->points[i]->tag = false;
			}
		}

		std::string getBestPathVectorsString(ACOPoint* ancestor, ACOPoint* start, ACOPoint* end, bool ignoreFirst = false) {

			double traveledDistance = 0;
			std::stringstream stream;
			std::map<long, bool> visitedPoints;

			while (start != end || ignoreFirst) {
				ignoreFirst = false;

				ACOPoint* next = 0;
				while (next == 0) {
					next = this->getNextPoint(ancestor, start, visitedPoints);
					if (next == 0 && this->isAllPointsVisited(visitedPoints)) {
						next = end;
					}
				}

				long x0 = start->coordinates[0];
				long y0 = start->coordinates[1];

				long x1 = next->coordinates[0];
				long y1 = next->coordinates[1];

				traveledDistance += euclidianDistance2d(x0, y0, x1, y1);

				stream << x0 << "\t" << y0 << "\t";
				stream << x1 - x0 << "\t" << y1 - y0 << "\t" << traveledDistance << "\n";

				ancestor = start;
				start = next;
			}

			return stream.rdbuf()->str();
		}

		bool isAllPointsVisited(std::map<long, bool>& visitedPoints) {

			if (visitedPoints.size() < this->pointsLentgh) return false;

			for (unsigned int i = 0; i < visitedPoints.size(); i++) {
				if (!visitedPoints[i]) return false;
			}

			return true;
		}

		ACOPoint* getNextPoint(ACOPoint* ancestor, ACOPoint* current, std::map<long, bool>& visitedPoints) {

			long index = 0;
			long bestIndex = 0;

			double weight = 0;
			double bestWeight = 0;

			// Mark current as visited by this ant;
			visitedPoints[current->index] = true;

			// Mark the ancestor as visited (if any)
			if (ancestor != 0) {
				visitedPoints[ancestor->index] = true;
			}

			// Calculate the total sum for probability
			for (unsigned int i = 0; i < current->connections.size(); i++) {

				//ignore visited connections
				if (visitedPoints[current->connections[i]->index]) continue;

				// Retrieves the weight
				index = current->connections[i]->index;
				weight = current->connectionsWeights[current->connections[i]->index];

				if (weight > bestWeight) {
					bestIndex = index;
					bestWeight = weight;
				}
			}

			return current->connections[bestIndex];
		}

		char* stringToChar(const std::string& s) {
			char* txt = new char[s.size() + 1];
			s.copy(txt, s.size() + 1);
			txt[s.size()] = '\0';
			return txt;
		}

	public:
		ACOPoint** points;
		unsigned int pointsLentgh;
		inline static double decayRate = 0.05;
		inline static double initialWeight = 0.01;
		inline static double initialBestWeight = 0.1;

		ACOMap(unsigned int neighborhoodSize) {
			this->pointsLentgh = neighborhoodSize;
			this->points = new ACOPoint*[neighborhoodSize];

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

			this->points[index] = new ACOPoint(2, index, x, y);
		}

		void traceConnections() {
			unsigned int checkedPointCounter = 0;

			ACOPoint* selectedPoint = 0;
			ACOPoint* from = 0;
			ACOPoint* to = 0;

			ACOPoint* first = 0;
			ACOPoint* last = 0;

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
					from->addConnection(to, ACOMap::initialWeight);

					if (to == from || to == 0 || to->tag) {
						continue;
					}

					tempDistance = euclidianDistance2d(from->coordinates[0], from->coordinates[1], to->coordinates[0], to->coordinates[1]);

					if (tempDistance < shortestDistance) {
						shortestDistance = tempDistance;
						selectedPoint = to;
					}
				}

				if (selectedPoint == 0) break;

				ACOPoint::setWeightBeetwen(from, selectedPoint, ACOMap::initialBestWeight);

				from->tag = true;
				from = selectedPoint;
				last = selectedPoint;

				checkedPointCounter++;
				selectedPoint = 0;
			}

			last->addConnection(first, ACOMap::initialBestWeight);
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

		void saveBestPath(ACOPoint* start, const char* path) {
			openFile(path);
			std::string s = this->getBestPathVectorsString(0, start, start, true);

			char* txt = stringToChar(s);
			writeCharsToFile(txt);
			closeFile();
		}
		void printBestPath(ACOPoint* start) {
			std::cout << this->getBestPathVectorsString(0, start, start, true);
		}
};

#endif /* SRC_LIB_ACOMAP_CPP_ */
