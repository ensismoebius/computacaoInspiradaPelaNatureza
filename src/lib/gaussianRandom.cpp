/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 */

#include "gaussianRandom.h"

#include <random>

// generate random number from hardware
std::default_random_engine generator;

// the type of random distributions
std::normal_distribution<double> normalDistribution(0.0, 1.0);
std::uniform_int_distribution<int> uniformDistribution(0, RAND_MAX);

// seed generator
std::mt19937 seed;

double getGaussionRandomPertubation() {
	return normalDistribution(generator) / 2.0;
}

int getUniformDistributedRandomPertubation() {
	return uniformDistribution(seed);
}
