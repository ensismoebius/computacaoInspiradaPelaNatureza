/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to minimize (2^(-2* ((x−0.1)/0.9)^ 2))*(sin(5πx))^6
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

#ifndef CLASS_GenExperiment02_CPP_
#define CLASS_GenExperiment02_CPP_

namespace geneticExperiments {

	/**
	 * Experiment to minimize (2^(-2* ((x−0.1)/0.9)^ 2))*(sin(5πx))^6
	 * using genetic algorithms;
	 */
	class Experiment02: public GeneticExperience {
		public:
			static const int populationSize = 4;
			static const int subjectSize = 32;

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

				for (int i = 0; i < populationSize; i++) {
					for (int j = 0; j < subjectSize; j++) {
						subject[j] = arrPopulation[(i * subjectSize) + j];
					}
					std::cout << convertIEEE754BinaryArrayToFloat(subject) << std::endl;
				}
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

			//subject size must be 32
			/**
			 * Fitness function
			 * @param arrSubject
			 * @param subjectSize
			 * @return
			 */
			static double fitness(char* arrSubject, int subjectSize) {
				(void) subjectSize; // suppress the unused warnings

				float x = convertIEEE754BinaryArrayToFloat(arrSubject);

				if (x > 1) return 5.0;
				if (x < 0) return 5.0;

				double p1 = -2.0 * pow((x - 0.1) / 0.9, 2.0);
				double p2 = pow(sin(5.0 * M_PI * x), 6.0);
				double final = (double) pow(2.0, p1) * p2;

				return 5.0 - final;
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
				std::cout << std::setprecision(10);

				// genotype block
				std::cout << "The best genotype is: ";
				for (int j = 0; j < subjectSize; j++) {
					std::cout << (unsigned int) (bestSubject[j]);
				}
				std::cout << std::endl << " or in numerical form: " << convertIEEE754BinaryArrayToFloat(bestSubject) << std::endl;

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
#endif /* CLASS_Experiment02_CPP_ */
