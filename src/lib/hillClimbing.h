/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 */

#ifndef LIB_HILLCLIMBING_H_
#define LIB_HILLCLIMBING_H_

double generateFirstValue();
double calculateStochasticProbability(double candidate, double bestResult, double tFactor, char minimize = 1);
double hillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath);
double stochasticHillClimbing(int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath);
double interactiveHillClimbing(int samplesAmount, int maxIterations, double targetValue, double (*fitnessFunction)(double), const char* filePath);

#endif /* LIB_HILLCLIMBING_H_ */
