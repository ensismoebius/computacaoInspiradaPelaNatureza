/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Contains of functions needed for Simulated annealing algorithms
 */

#include <cmath>
#include <cstdlib>

#include "fileWriter.h"
#include "gaussianRandom.h"
#include "stochasticProbability.h"

/**
 * Simulated annealing
 * @description
 * Compared to hill climbing and its variations, simulated annealing does
 * not shown particularly good results, it looks slower and his precision
 * are lower compared to hill climbing algorithms
 */
double simulated_annealing(double systemTemperature, double targetValue, double (*fitnessFunction)(double), const char* filePath) {

	openFile(filePath);

	// generating the first bestResult
	double bestResult;
	do {
		bestResult = fabs(getGaussionRandomPertubation());
	} while (bestResult > 0 && bestResult > 1);

	if ((*fitnessFunction)(bestResult) == targetValue) {
		return bestResult;
	}

	// Just stops when systemTemperature drops to almost 0
	while (systemTemperature > 0.0001) {

		double candidate;
		do {
			candidate = fabs(bestResult + getGaussionRandomPertubation());
		} while (candidate > 0 && candidate > 1);

		writeNumberToFile(candidate);

		if ((*fitnessFunction)(candidate) < (*fitnessFunction)(bestResult)) {
			bestResult = candidate;
		} else {
			double prob1 = double(rand()) / double(RAND_MAX);
			double prob2 = calculateStochasticProbability((*fitnessFunction)(candidate), (*fitnessFunction)(bestResult), systemTemperature, 1);

			if (prob1 < prob2) {
				bestResult = candidate;
			}
		}

		systemTemperature *= 0.99999;
	}

	closeFile();

	return bestResult;
}

