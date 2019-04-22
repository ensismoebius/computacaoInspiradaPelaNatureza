/*
 * Experiment04.cpp
 *
 *  Created on: 22 de abr de 2019
 *      Author: ensis
 */

#include <stddef.h>
#include <cmath>
#include <iostream>
#include <limits>

#include "../lib/Gen.cpp"
#include "../lib/variables.h"
#include "GeneticExperience.cpp"

#ifndef CLASS_Experiment04_CPP_
#define CLASS_Experiment04_CPP_

class Experiment04: public GeneticExperience {
public:
	static const int populationSize = 4;
	static const int subjectSize = 64;

	//subject size must be 64
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

	static void genesisFunction(char* arrPopulation, int populationSize, int subjectSize) {
		int genesAmount = populationSize * subjectSize;

		while (genesAmount--) {
			arrPopulation[genesAmount] = 0;
		}
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
		std::cout << std::endl << "Or in numerical form " << convertIEEE754BinaryArrayToFloat(bestSubject);
		std::cout << " , " << convertIEEE754BinaryArrayToFloat(bestSubject + (subjectSize / 2)) << std::endl;

		// phenotype block
		std::cout << "And his phenotype is " << bestValue << std::endl;

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
#endif /* CLASS_Experiment04_CPP_ */
