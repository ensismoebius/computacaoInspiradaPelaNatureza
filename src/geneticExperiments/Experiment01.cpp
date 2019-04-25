/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to find the subject { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 }
 * using genetic algorithms;
 */

#include <bits/types/FILE.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "GeneticExperience.cpp"

#ifndef CLASS_GenExperiment01_CPP_
#define CLASS_GenExperiment01_CPP_

namespace geneticExperiments {

	/**
	 * Experiment to find the subject { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 }
	 * using genetic algorithms;
	 */
	class Experiment01: public GeneticExperience {
		public:
			static const int populationSize = 4;
			static const int subjectSize = 12;

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
				if (score > 0) return;

				for (int i = 0; i < populationSize; i++) {
					for (int j = 0; j < subjectSize; j++) {
						std::cout << (int) arrPopulation[(i * subjectSize) + j] << ",";
						if ((j + 1) % 3 == 0) std::cout << std::endl;
					}
					std::cout << std::endl;
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
				// initializes the population
				while (genesAmount--) {
					arrPopulation[genesAmount] = random() > RAND_MAX / 2 ? 1 : 0;
				}

			}

			// subjectSize must be 12
			/**
			 * Fitness function
			 * @param arrSubject
			 * @param subjectSize
			 * @return
			 */
			static double fitness(char* arrSubject, int subjectSize) {
				double score = 0;
				int index = subjectSize;

				const char targetSubject[12] = { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 };

				while (index--) {
					score += arrSubject[index] != targetSubject[index] ? 1 : 0;
				}
				return score;
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

				// Finding the best and worst values
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
				std::cout << "Genetic experiment 01 - The best genotype is: ";
				for (int j = 0; j < subjectSize; j++) {
					std::cout << (unsigned int) (bestSubject[j]);
				}

				// phenotype block
				std::cout << " and his phenotype is: " << std::endl;
				for (int j = 0; j < subjectSize; j++) {
					std::cout << (int) bestSubject[j] << ",";
					if ((j + 1) % 3 == 0) std::cout << std::endl << std::endl;
				}
				std::cout << std::endl;

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
#endif /* CLASS_Experiment01_CPP_ */
