#include <cmath>
#include <cstdlib>
#include <iostream>

#include "../lib/hillClimbing.h"

#ifndef CLASS_HillExperiment01_CPP_
#define CLASS_HillExperiment01_CPP_

namespace hillClimbingAnnealingExperiments {

	class Experiment01 {

	public:
		/**
		 * Lesser the value, better the fitness
		 */
		static double fitnness(double x) {
			// we want to minimize the function to zero
			// so we must take only the absolute values
			// the nearer absolute values are from zero the better
			return abs(pow(x, 3.0) + x + 3);
		}

		static void perform(unsigned int iterations) {
			double results = hillClimbing(iterations, 0, fitnness);
			std::cout << "Result for abs(pow(x, 3.0) + x + 3) with " << iterations;
			std::cout << " and target value 0 using Hill Climbing: " << results;
		}
	};
}

#endif /* CLASS_HillExperiment01_CPP_ */
