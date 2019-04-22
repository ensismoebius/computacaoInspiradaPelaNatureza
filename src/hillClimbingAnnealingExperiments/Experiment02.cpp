#include <cmath>

#include "../lib/hillClimbing.h"

#ifndef CLASS_HillExperiment02_CPP_
#define CLASS_HillExperiment02_CPP_

namespace hillClimbingAnnealingExperiments {

	class Experiment02 {

	public:
		static double results;

		/**
		 * Bigger the value, better the fitness
		 */
		static double fitnness(double x) {
			// This was made to better understand
			// the expression, we do not really need it
			double r1 = (x - 0.1) / 0.9;
			double p1 = pow(r1, 2);
			double m1 = -2 * p1;
			double p2 = pow(2, m1);
			double p3 = pow(sin(5 * M_PI * x), 6);
			return p2 * p3;
		}

		static void perform(unsigned int iterations) {
			results = 0;
					//stochasticHillClimbing(iterations, 0, fitnness);
		}

	};
}

#endif /* GeneticExperience_CPP_ */