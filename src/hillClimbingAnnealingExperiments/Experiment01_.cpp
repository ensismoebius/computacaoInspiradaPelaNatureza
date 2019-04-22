//#include <cmath>
//#include <cstdlib>
//
//#include "../lib/hillClimbing.h"
//#include "Experiment.cpp"
//
//#ifndef CLASS_HillExperiment01_CPP_
//#define CLASS_HillExperiment01_CPP_
//
//namespace hillClimbingAnnealingExperiments {
//
//	class Experiment01: public Experiment {
//
//	public:
//		/**
//		 * Lesser the value, better the fitness
//		 */
//		static double fitnness(double x) {
//			// we want to minimize the function to zero
//			// so we must take only the absolute values
//			// the nearer absolute values are from zero the better
//			return abs(pow(x, 3.0) + x + 3);
//		}
//
//		static void perform(unsigned int iterations) {
//			results = hillClimbing(iterations, 0, fitnness);
//		}
//	};
//}
//
//#endif /* CLASS_HillExperiment01_CPP_ */
