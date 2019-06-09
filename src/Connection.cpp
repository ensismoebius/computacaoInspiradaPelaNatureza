/*
 * Coonection.h
 *
 *  Created on: 9 de jun de 2019
 *      Author: ensis
 */

#ifndef SRC_COONECTION_CPP_
#define SRC_COONECTION_CPP_

class Connection {
	public:
		double* from;
		double* to;
		double weight;

		Connection(double*& from, double weight, double*& to) {
			this->to = to;
			this->from = from;
			this->weight = weight;
		}

};

#endif /* SRC_COONECTION_CPP_ */
