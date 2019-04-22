#ifndef CLASS_HillExperiment01_CPP_
#define CLASS_HillExperiment01_CPP_

namespace hillClimbingAnnealingExperiments {

	class Experiment01 {

	public:
		static double results;

		/**
		 * Bigger the value, better the fitness
		 */
		static double fitnness(double x) {
			return x;
		}

		static void perform(unsigned int iterations) {
			(void) iterations;
			results = 0;
		}

	};
}

#endif /* GeneticExperience_CPP_ */
