/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to minimize x^3.0 + x + 3
 * using interactive hill climbing;
 */

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "../lib/hillClimbing.h"

#ifndef CLASS_HillExperiment03_CPP_
#define CLASS_HillExperiment03_CPP_

namespace hillClimbingAnnealingExperiments {

	/**
	 * Experiment to minimize x^3.0 + x + 3
	 * using interactive hill climbing;
	 */
	class Experiment03 {

		public:

			/**
			 * Lesser the value, better the fitness
			 * @param x
			 * @return Lesser the value, better the fitness
			 */
			static double fitnness(double x) {
				// we want to minimize the function to zero
				// so we must take only the absolute values
				// the nearer absolute values are from zero the better
				return abs(pow(x, 3.0) + x + 3);
			}

			/**
			 * Starts the experiment!!!
			 * @param iterations - Number of interactions
			 * @param filePath - File path to save experiment data
			 */
			static void perform(unsigned int iterations, const char* filePath) {

				// If we don't do this cout messes up with our values
				std::cout << std::fixed;
				std::cout << std::setprecision(6);

				double results = interactiveHillClimbing(10, iterations, fitnness, filePath);
				std::cout << "Hill-Anna experiment 03 - Result for minimization of x^3.0 + x + 3 with " << iterations;
				std::cout << " iterations using Interactive Hill Climbing: " << results << std::endl << std::endl;

			}

	};
}

#endif /* CLASS_HillExperiment03_CPP_ */
