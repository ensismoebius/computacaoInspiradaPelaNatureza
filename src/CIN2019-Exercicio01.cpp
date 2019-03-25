/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This hole project are under GPLv3, for
 * more information read the license file
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include "lib/annealing.h"
#include "lib/hillClimbing.h"

/**
 * Lesser the value, better the fitness
 */
double fitnness1(double x) {
	// we want to minimize the function to zero
	// so we must take only the absolute values
	// the nearer absolute values are from zero the better
	return abs(pow(x, 3.0) + x + 3);
}

/**
 * Bigger the value, better the fitness
 */
double fitnness2(double x) {
	// This was made to better understand
	// the expression, we do not really need it
	double r1 = (x - 0.1) / 0.9;
	double p1 = pow(r1, 2);
	double m1 = -2 * p1;
	double p2 = pow(2, m1);
	double p3 = pow(sin(5 * M_PI * x), 6);
	return p2 * p3;
}

int main() {
	double bestResult;

	// hill climbing algorithms
	bestResult = hillClimbing(10000, 0, fitnness1);
	bestResult = stochasticHillClimbing(10000, 0, fitnness1);
	bestResult = interactiveHillClimbing(10, 10000, 0, fitnness1);

	// annealing algorithms
	bestResult = simulated_annealing(1000, std::numeric_limits<double>::max(), fitnness2);
	std::cout << bestResult << std::endl;
	return 0;
}
