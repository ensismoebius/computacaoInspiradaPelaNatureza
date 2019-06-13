/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 10 de jun de 2019
 *
 */

#ifndef SRC_LIB_ACOPOINT_CPP_
#define SRC_LIB_ACOPOINT_CPP_

#include <map>
#include <vector>
#include <cstdarg>
#include <stdexcept>
#include <algorithm>

class ACOPoint {
	public:
		unsigned int index;
		bool tag = false;
		std::map<unsigned int, double> connectionsWeights;
		std::map<unsigned int, ACOPoint*> connections;
		std::vector<long> coordinates;

		ACOPoint(unsigned int dimension, unsigned int index, ...) {

			this->index = index;

			va_list coordinates;
			va_start(coordinates, index);

			for (unsigned int i = 0; i < dimension; i++) {
				this->coordinates.push_back(va_arg(coordinates, long));
			}

			va_end(coordinates);
		}

		void addConnection(ACOPoint* point, double weight) {

			if (point == 0) return;

			point->connections[this->index] = this;
			point->connectionsWeights[this->index] = weight;

			this->connections[point->index] = point;
			this->connectionsWeights[point->index] = weight;
		}

		static void addWeightBeetwen(ACOPoint* one, ACOPoint* two, double amount) {
			double weight = one->connectionsWeights[two->index];
			weight += amount;
			setWeightBeetwen(one, two, weight);
		}

		static void setWeightBeetwen(ACOPoint* one, ACOPoint* two, double weight) {
			one->connectionsWeights[two->index] = weight;
			two->connectionsWeights[one->index] = weight;
		}
};

#endif /* SRC_LIB_ACOPOINT_CPP_ */
