/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This hole project are under GPLv3, for
 * more information read the license file
 */

#ifndef LIB_HILLCLIMBING_H_
#define LIB_HILLCLIMBING_H_

double generateFirstValue();
double hillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double));
double stochasticHillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double));
double calculateStochasticProbability(double candidate, double bestResult, double tFactor, char minimize = 1);
double interactiveHillClimbing(int samplesAmount, int maxIterations, double targetValue, double (*fitnessFunction)(double));

#endif /* LIB_HILLCLIMBING_H_ */
