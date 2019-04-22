#include <cmath>
#include <cstdlib>

#include "../lib/hillClimbing.h"

#ifndef CLASS_HillExperiment03_CPP_
#define CLASS_HillExperiment03_CPP_

namespace hillClimbingAnnealingExperiments {

	class Experiment03 {

	public:

		static double results;

		static double fitnness(double x) {
			// we want to minimize the function to zero
			// so we must take only the absolute values
			// the nearer absolute values are from zero the better
			return abs(pow(x, 3.0) + x + 3);
		}

		static void perform(unsigned int iterations) {
			results = interactiveHillClimbing(10, iterations, 0, fitnness);
		}

	};
}

#endif /* GeneticExperience_CPP_ */
