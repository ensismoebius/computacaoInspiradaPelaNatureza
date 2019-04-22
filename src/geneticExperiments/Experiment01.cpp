#include <cstdlib>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "GeneticExperience.cpp"

#ifndef CLASS_Experiment01_CPP_
#define CLASS_Experiment01_CPP_

class Experiment01: public GeneticExperience {
public:
	static const int populationSize = 4;
	static const int subjectSize = 12;

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
	static void genesisFunction(char* arrPopulation, int populationSize, int subjectSize) {
		int genesAmount = populationSize * subjectSize;
		// initializes the population
		while (genesAmount--) {
			arrPopulation[genesAmount] = random() > RAND_MAX / 2 ? 1 : 0;
		}

	}

	// subjectSize must be 12
	static double fitness(char* arrSubject, int subjectSize) {
		double score = 0;
		int index = subjectSize;

		const char targetSubject[12] = { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 };

		while (index--) {
			score += arrSubject[index] != targetSubject[index] ? 1 : 0;
		}
		return score;
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

		// phenotype block
		std::cout << " And his phenotype is:" << std::endl;
		for (int j = 0; j < subjectSize; j++) {
			std::cout << (int) bestSubject[j] << ",";
			if ((j + 1) % 3 == 0) std::cout << std::endl;
		}
		std::cout << std::endl;

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
#endif /* CLASS_Experiment01_CPP_ */
