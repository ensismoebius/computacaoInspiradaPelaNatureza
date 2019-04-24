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
#ifndef LIB_ANNEALING_H_
#define LIB_ANNEALING_H_

double simulated_annealing(double systemTemperature, double targetValue, double (*fitnessFunction)(double), const char* filePath);

#endif /* LIB_ANNEALING_H_ */
