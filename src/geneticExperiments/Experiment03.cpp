/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * Experiment to maximize -x^2 * sin(x)
 * using genetic algorithms;
 */
#include <cmath>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "../lib/variables.h"
#include "Experiment02.cpp"

#ifndef CLASS_GenExperiment03_CPP_
#define CLASS_GenExperiment03_CPP_

namespace geneticExperiments {

	/**
	 * Experiment to maximize -x^2 * sin(x)
	 * using genetic algorithms;
	 */
	class Experiment03: public Experiment02 {
		public:
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

				if (x > 0) return 50.0;
				if (x < -10) return 50.0;

				double final = pow(-x, 2) * sin(x);

				return 50.0 - final;
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

				// genotype block
				std::cout << "The best genotype is ";
				for (int j = 0; j < subjectSize; j++) {
					std::cout << (unsigned int) (bestSubject[j]);
				}
				std::cout << std::endl << "Or in numerical form " << convertIEEE754BinaryArrayToFloat(bestSubject) << std::endl;

				// phenotype block
				std::cout << " And his phenotype is " << bestValue << std::endl << std::endl;

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
#endif /* CLASS_Experiment03_CPP_ */
