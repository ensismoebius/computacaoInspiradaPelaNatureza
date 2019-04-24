/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to maximize (2^(-2* ((x−0.1)/0.9)^ 2))*(sin(5πx))^6
 * using interactive hill climbing;
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "../lib/hillClimbing.h"

#ifndef CLASS_HillExperiment05_CPP_
#define CLASS_HillExperiment05_CPP_

namespace hillClimbingAnnealingExperiments {

	/**
	 * Experiment to maximize (2^(-2* ((x−0.1)/0.9)^ 2))*(sin(5πx))^6
	 * using interactive hill climbing;
	 */
	class Experiment05 {

		public:

			/**
			 * Lesser the value, better the fitness
			 * @param x
			 * @return Lesser the value, better the fitness
			 */
			static double fitnness(double x) {
				// This was made to better understand
				// the expression, we do not really need it
				double r1 = (x - 0.1) / 0.9;
				double p1 = pow(r1, 2);
				double m1 = -2 * p1;
				double p2 = pow(2, m1);
				double p3 = pow(sin(5 * M_PI * x), 6);
				return std::numeric_limits<char>::max() - (p2 * p3);
			}

			/**
			 * Starts the experiment!!!
			 * @param iterations - Number of interactions
			 * @param filePath - File path to save experiment data
			 */
			static void perform(unsigned int iterations, const char* filePath) {

				// If we don't do this cout messes up with our values
				std::cout << std::fixed;
				std::cout << std::setprecision(10);

				double results = hillClimbing(iterations, fitnness, filePath);
				std::cout << "Result for maximization of (2^(-2 * ((x - 0.1) / 0.9)^2)) * (sin(5 * M_PI * x)^6 with " << iterations;
				std::cout << " iterations using Hill Climbing: " << results << std::endl << std::endl;

			}

	};
}

#endif /* CLASS_HillExperiment05_CPP_ */
