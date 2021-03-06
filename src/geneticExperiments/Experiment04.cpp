/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to minimize f (x, y) = (1 − x )^2 + 100(y − x^2 )^2
 * using genetic algorithms;
 */

#include <bits/types/FILE.h>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "../lib/variables.h"
#include "GeneticExperience.cpp"

#ifndef CLASS_GenExperiment04_CPP_
#define CLASS_GenExperiment04_CPP_

namespace geneticExperiments {

	/**
	 * Experiment to minimize f (x, y) = (1 − x )^2 + 100(y − x^2 )^2
	 * using genetic algorithms;
	 */
	class Experiment04: public GeneticExperience {
		public:
			static const int populationSize = 4;
			static const int subjectSize = 64;

			//subject size must be 64
			/**
			 * Fitness function
			 * @param arrSubject
			 * @param subjectSize
			 * @return
			 */
			static double fitness(char* arrSubject, int subjectSize) {

				float x = convertIEEE754BinaryArrayToFloat(arrSubject);
				float y = convertIEEE754BinaryArrayToFloat(arrSubject + (subjectSize / 2));

				if (x > 5) return 50.0;
				if (x < -5) return 50.0;

				if (y > 5) return 50.0;
				if (y < -5) return 50.0;

				double final = pow((1 - x), 2) + 100 * pow((y - pow(x, 2)), 2);

				return final;
			}

			/**
			 * Print value of subjects in console
			 * @param arrPopulation
			 * @param populationSize
			 * @param subjectSize
			 * @param generation
			 * @param score
			 */
			static void print(char* arrPopulation, int populationSize, int subjectSize, int generation, double score) {
				std::cout << "Generation: " << generation << " Score:" << score << std::endl;
				char* subject = new char[32];
				int j;

				for (int i = 0; i < populationSize; i++) {
					for (j = 0; j < subjectSize / 2; j++) {
						subject[j] = arrPopulation[(i * subjectSize) + j];
					}
					std::cout << convertIEEE754BinaryArrayToFloat(subject) << std::endl;

					for (; j < subjectSize; j++) {
						subject[j - (subjectSize / 2)] = arrPopulation[(i * subjectSize) + j];
					}
					std::cout << convertIEEE754BinaryArrayToFloat(subject) << std::endl;
				}

				delete[] subject;
				subject = NULL;
			}

			/**
			 * Generate the first population
			 * @param arrPopulation
			 * @param populationSize
			 * @param subjectSize
			 */
			static void genesisFunction(char* arrPopulation, int populationSize, int subjectSize) {

				int genesAmount = populationSize * subjectSize;

				while (genesAmount--) {
					arrPopulation[genesAmount] = 0;
				}
			}

			/**
			 * Prints the final result in console
			 * @param subjectSize
			 * @param populationSize
			 * @param arrPopulation
			 */
			static void showFinalResults(int subjectSize, int populationSize, char* arrPopulation) {
				double temp = 0;
				double bestValue = std::numeric_limits<double>::max();
				double worstValue = 0;

				char* bestSubject = new char[subjectSize];

				// Finding the best
				for (int i = 0; i < populationSize; i++) {

					temp = fitness(arrPopulation + (subjectSize * i), subjectSize);

					if (temp < bestValue) {
						bestValue = temp;
						for (int j = 0; j < subjectSize; j++) {
							bestSubject[j] = (arrPopulation + (subjectSize * i))[j];
						}
					}

					if (temp > worstValue) {
						worstValue = temp;
					}
				}

				// If we don't do this cout messes up with our values
				std::cout << std::fixed;
				std::cout << std::setprecision(6);

				// genotype block
				std::cout << "Genetic experiment 04 - The best genotype is: ";
				for (int j = 0; j < subjectSize; j++) {
					std::cout << (unsigned int) (bestSubject[j]);
				}
				std::cout << std::endl << " or in numerical form: x=" << convertIEEE754BinaryArrayToFloat(bestSubject);
				std::cout << " and y=" << convertIEEE754BinaryArrayToFloat(bestSubject + (subjectSize / 2)) << std::endl;

				// phenotype block
				std::cout << " and his phenotype is: " << bestValue << std::endl << std::endl;

				delete[] bestSubject;
			}

			/**
			 * Perform the experience!!
			 * @param maxIterations - Number of interactions
			 * @param filePath - File path to save experiment data
			 */
			static void perform(unsigned int maxIterations, const char* filePath) {

				FILE * pFile;
				pFile = fopen(filePath, "w");

				Gen pop = Gen(subjectSize, populationSize, fitnessWeight, diversityWeight, crossoverRate, mutationRate, fitness, print, genesisFunction);

				pop.setFilewriter(pFile);

				unsigned int counter = 0;
				while (pop.getBestScore() > 0 && counter < maxIterations) {
					pop.evaluateAllSubjects();
					pop.selectTheBestSubjects();
					pop.createNextGeneration();
					counter++;
				}

				char* arrPopulation = pop.getArrPopulation();
				showFinalResults(subjectSize, populationSize, arrPopulation);
				delete[] arrPopulation;

				fclose(pFile);
			}
	};

}
#endif /* CLASS_Experiment04_CPP_ */
