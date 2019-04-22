//void print1(char* arrPopulation, int populationSize, int subjectSize, int generation, double score) {
//	std::cout << "Generation: " << generation << " Score:" << score << std::endl;
//	if (score > 0) return;
//
//	for (int i = 0; i < populationSize; i++) {
//		for (int j = 0; j < subjectSize; j++) {
//			std::cout << (int) arrPopulation[(i * subjectSize) + j] << ",";
//			if ((j + 1) % 3 == 0) std::cout << std::endl;
//		}
//		std::cout << std::endl;
//	}
//}
//void genesisFunction1(char* arrPopulation, int populationSize, int subjectSize) {
//	int genesAmount = populationSize * subjectSize;
//	char* population = new char[genesAmount];
//
//	// initializes the population
//	while (genesAmount--) {
//		population[genesAmount] = random() > RAND_MAX / 2 ? 1 : 0;
//	}
//
//	return population;
//}
//
//// subjectSize must be 12
//double fitness1(char* arrSubject, int subjectSize) {
//	double score = 0;
//	int index = subjectSize;
//
//	const char targetSubject[12] = { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 };
//
//	while (index--) {
//		score += arrSubject[index] != targetSubject[index] ? 1 : 0;
//	}
//	return score;
//}

#include <stddef.h>
#include <cmath>
#include <iostream>
#include <limits>

#include "lib/Gen.cpp"
#include "lib/variables.h"

void print2(char* arrPopulation, int populationSize, int subjectSize, int generation, double score) {
	std::cout << "Generation: " << generation << " Score:" << score << std::endl;
	char* subject = new char[32];

	for (int i = 0; i < populationSize; i++) {
		for (int j = 0; j < subjectSize; j++) {
			subject[j] = arrPopulation[(i * subjectSize) + j];
		}
		std::cout << convertIEEE754BinaryArrayToFloat(subject) << std::endl;
	}
}

void genesisFunction2(char* arrPopulation, int populationSize, int subjectSize) {
	int genesAmount = populationSize * subjectSize;

	while (genesAmount--) {
		arrPopulation[genesAmount] = 0;
	}
}

//subject size must be 32
double fitness2(char* arrSubject, int subjectSize) {
	float x = convertIEEE754BinaryArrayToFloat(arrSubject);

	if (x > 1) return 5.0;
	if (x < 0) return 5.0;

	std::cout << x << std::endl;

	double p1 = -2.0 * pow((x - 0.1) / 0.9, 2.0);
	double p2 = pow(sin(5.0 * M_PI * x), 6.0);
	double final = (double) pow(2.0, p1) * p2;

	return 5.0 - final;
}

//subject size must be 32
double fitness3(char* arrSubject, int subjectSize) {
	float x = convertIEEE754BinaryArrayToFloat(arrSubject);

	if (x > 0) return 50.0;
	if (x < -10) return 50.0;

	double final = pow(-x, 2) * sin(x);

	return 50.0 - final;
}

//subject size must be 64
double fitness4(char* arrSubject, int subjectSize) {

	float x = convertIEEE754BinaryArrayToFloat(arrSubject);
	float y = convertIEEE754BinaryArrayToFloat(arrSubject + (subjectSize / 2));

	if (x > 5) return 50.0;
	if (x < -5) return 50.0;

	if (y > 5) return 50.0;
	if (y < -5) return 50.0;

	double final = pow((1 - x), 2) + 100 * pow((y - pow(x, 2)), 2);

	return final;
}

void print4(char* arrPopulation, int populationSize, int subjectSize, int generation, double score) {
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

void showFinalResults(int subjectSize, int populationSize, char* arrPopulation) {
	double temp = 0;
	double bestValue = std::numeric_limits<double>::max();

	char* bestSubject = new char[subjectSize];

	for (int i = 0; i < populationSize; i++) {

		temp = fitness4(arrPopulation + (subjectSize * i), subjectSize);

		if (temp < bestValue) {

			bestValue = temp;

			for (int j = 0; j < subjectSize; j++) {
				bestSubject[j] = (arrPopulation + (subjectSize * i))[j];
			}
		}
	}

	std::cout << "The best genotype is ";
	for (int j = 0; j < subjectSize; j++) {
		std::cout << (unsigned int) (bestSubject[j]);
	}
	std::cout << std::endl << "Or in numerical form " << convertIEEE754BinaryArrayToFloat(bestSubject);
	std::cout << " , " << convertIEEE754BinaryArrayToFloat(bestSubject + (subjectSize / 2)) << std::endl;

	std::cout << "And his phenotype is " << bestValue << std::endl;

	delete[] bestSubject;
}

int main() {

	int subjectSize = 64;
	int populationSize = 4;
	double fitnessWeight = 8;
	double diversityWeight = 2;
	double crossoverRate = 0.4;
	double mutationRate = 0.1;

	Gen pop = Gen(subjectSize, populationSize, fitnessWeight, diversityWeight, crossoverRate, mutationRate, fitness4, print4, genesisFunction2);

	pop.printPopulation();

	int counter = 0;
	while (pop.getBestScore() > 0 && counter < 100000) {
		pop.evaluateAllSubjects();
		pop.selectTheBestSubjects();
		pop.createNextGeneration();
		counter++;
	}

	pop.printPopulation();
	char* arrPopulation = pop.getArrPopulation();
	showFinalResults(subjectSize, populationSize, arrPopulation);
	delete[] arrPopulation;
	return 0;
}
