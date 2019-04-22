#include <cmath>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "../lib/variables.h"
#include "Experiment02.cpp"

#ifndef CLASS_GenExperiment03_CPP_
#define CLASS_GenExperiment03_CPP_

namespace geneticExperiments {

	class Experiment03: public Experiment02 {
	public:
		//subject size must be 32
		static double fitness(char* arrSubject, int subjectSize) {
			(void) subjectSize; // suppress the unused warnings

			float x = convertIEEE754BinaryArrayToFloat(arrSubject);

			if (x > 0) return 50.0;
			if (x < -10) return 50.0;

			double final = pow(-x, 2) * sin(x);

			return 50.0 - final;
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
#endif /* CLASS_Experiment03_CPP_ */
