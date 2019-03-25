/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This hole project are under GPLv3, for
 * more information read the license file
 */

#include <cmath>

/**
 * Return a number between 0 and 1 representing the
 * probability of the candidate be the new bestResult
 *
 * Forward - first option (a.k.a. next should be bigger)
 * candidate bigger than bestResult result in bigger probabilities
 *
 * Backward - second option (a.k.a. next should be lower)
 * candidate lower than bestResult result in bigger probabilities
 */
double calculateStochasticProbability(double candidate, double bestResult, double tFactor, char forward) {
	return forward ? (1.0 / (1.0 + exp((bestResult - candidate) / tFactor))) : (1.0 / (1.0 + exp((candidate - bestResult) / tFactor)));
}

