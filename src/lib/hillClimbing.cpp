/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 */

#include <cstdlib>

#include "fileWriter.h"
#include "gaussianRandom.h"
#include "stochasticProbability.h"

/**
 * Hill climbing algorithm
 *
 * @description
 * The algorithm (as predicted) are particularly sensible to the initial value
 * of the bestResult variable, it takes a while, to find suitable values that
 * the algorithm accepts to give us some usable results. Its is sensible to
 * perturbation too it takes a long time to find and build a suitable value
 * generator
 */
double hillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath) {

	openFile(filePath);

	double bestResult = getGaussionRandomPertubation() + 1.0;

	if ((*fitnessFunction)(bestResult) == targetValue) {
		return bestResult;
	}
	while (maxIterations-- && (*fitnessFunction)(bestResult) != targetValue) {
		double candidate = bestResult + getGaussionRandomPertubation();

		writeFile(candidate);

		if ((*fitnessFunction)(candidate) < (*fitnessFunction)(bestResult)) {
			bestResult = candidate;
		}
	}

	closeFile();
	return bestResult;
}

/**
 * Interactive hill climbing
 * @description
 * The same happens as the regular hill climbing, the only difference are that,
 * having multiple starting points, the probabilities to find an result is better
 */
double interactiveHillClimbing(int samplesAmount, int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath) {

	openFile(filePath);

	double globalBestResult = getGaussionRandomPertubation() + 1.0;

	while (samplesAmount-- && (*fitnessFunction)(globalBestResult) != 0) {

		double localBestResult = getGaussionRandomPertubation() + 1.0;

		writeFile(localBestResult);

		if ((*fitnessFunction)(localBestResult) == targetValue) {
			return localBestResult;
		}

		localBestResult = hillClimbing(maxIterations, targetValue, (*fitnessFunction), filePath);

		if ((*fitnessFunction)(localBestResult) < (*fitnessFunction)(globalBestResult)) {
			globalBestResult = localBestResult;
		}
	}

	closeFile();

	return globalBestResult;
}

/**
 * Stochastic hill climbing
 * Here the tFactor play a great hole!
 *
 * The bigger tFactor are, the bigger must
 * be the difference between the values in
 * order to get higher probabilities of the
 * candidate be the new bestResult.
 */
double stochasticHillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath) {

	openFile(filePath);

	// the bigger tFactor are, the bigger must
	// be the difference between the values in
	// order to get higher probabilities to the
	// candidate be the new bestResult
	double tFactor = .5;
	double bestResult = getGaussionRandomPertubation() + 1.0;

	if ((*fitnessFunction)(bestResult) == targetValue) {
		return bestResult;
	}
	while (maxIterations-- && (*fitnessFunction)(bestResult) != targetValue) {
		double candidate = bestResult + getGaussionRandomPertubation();

		writeFile(candidate);

		if ((*fitnessFunction)(candidate) == targetValue) {
			return candidate;
		}

		double prob1 = double(rand()) / double(RAND_MAX);
		double prob2 = calculateStochasticProbability((*fitnessFunction)(candidate), (*fitnessFunction)(bestResult), tFactor, 0);

		if (prob1 < prob2) {
			bestResult = candidate;
		}
	}

	closeFile();

	return bestResult;
}

