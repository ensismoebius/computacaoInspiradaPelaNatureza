/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Calculates stochastic probability
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
double calculateStochasticProbability(double evalCandidate, double evalBestResult, double tFactor, char forward) {
	if (forward) {
		return (1.0 / (1.0 + exp((evalBestResult - evalCandidate) / tFactor)));
	} else {
		return (1.0 / (1.0 + exp((evalCandidate - evalBestResult) / tFactor)));
	}
}

