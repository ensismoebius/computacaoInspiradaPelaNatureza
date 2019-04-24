/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 * 
 * 24 de abr de 2019
 * 
 *  This library are responsible for generating random numbers 
 */

#include "gaussianRandom.h"

#include <random>

/**
 * generate random number from hardware
 */
std::default_random_engine generator;

/**
 * the type of random distributions
 */
std::normal_distribution<double> normalDistribution(0.0, 1.0);
std::uniform_int_distribution<int> uniformDistribution(0, RAND_MAX);

/**
 * seed generator
 */
std::mt19937 seed;

/**
 * Generate a normal distribution random number 
 * @return normal distribution random number
 */
double getGaussionRandomPertubation() {
	return normalDistribution(generator) / 2.0;
}

/**
 * Generate a uniform distributed random number
 * @return uniform distributed random number
 */
int getUniformDistributedRandomPertubation() {
	return uniformDistribution(seed);
}
