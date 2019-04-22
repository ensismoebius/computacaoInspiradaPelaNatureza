#include <cmath>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "../lib/variables.h"
#include "GeneticExperience.cpp"

#ifndef CLASS_GenExperiment02_CPP_
#define CLASS_GenExperiment02_CPP_

namespace geneticExperiments {
	class Experiment02: public GeneticExperience {
	public:
		static const int populationSize = 4;
		static const int subjectSize = 32;

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

		static void genesisFunction(char* arrPopulation, int populationSize, int subjectSize) {
			int genesAmount = populationSize * subjectSize;

			while (genesAmount--) {
				arrPopulation[genesAmount] = 0;
			}
		}

		//subject size must be 32
		static double fitness(char* arrSubject, int subjectSize) {
			(void) subjectSize; // suppress the unused warnings

			float x = convertIEEE754BinaryArrayToFloat(arrSubject);

			if (x > 1) return 5.0;
			if (x < 0) return 5.0;

			std::cout << x << std::endl;

			double p1 = -2.0 * pow((x - 0.1) / 0.9, 2.0);
			double p2 = pow(sin(5.0 * M_PI * x), 6.0);
			double final = (double) pow(2.0, p1) * p2;

			return 5.0 - final;
		}

		static void showFinalResults(int subjectSize, int populationSize, char* arrPopulation) {
			double temp = 0;
			double bestValue = std::numeric_limits<double>::max();

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
			}

			// genotype block
			std::cout << "The best genotype is ";
			for (int j = 0; j < subjectSize; j++) {
				std::cout << (unsigned int) (bestSubject[j]);
			}
			std::cout << std::endl << "Or in numerical form " << convertIEEE754BinaryArrayToFloat(bestSubject) << std::endl;

			// phenotype block
			std::cout << " And his phenotype is " << bestValue << std::endl;

			delete[] bestSubject;
		}

		static void perform(unsigned int maxIterations) {
			Gen pop = Gen(subjectSize, populationSize, fitnessWeight, diversityWeight, crossoverRate, mutationRate, fitness, print, genesisFunction);

			pop.printPopulation();

			unsigned int counter = 0;
			while (pop.getBestScore() > 0 && counter < maxIterations) {
				pop.evaluateAllSubjects();
				pop.selectTheBestSubjects();
				pop.createNextGeneration();
				counter++;
			}

			pop.printPopulation();
			char* arrPopulation = pop.getArrPopulation();
			showFinalResults(subjectSize, populationSize, arrPopulation);
			delete[] arrPopulation;
		}

	};
}
#endif /* CLASS_Experiment02_CPP_ */
