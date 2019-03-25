/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 */

#include "gaussianRandom.h"

#include <random>

std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0, 1.0);

double getGaussionRandomPertubation() {
	return distribution(generator) / 2.0;
}

