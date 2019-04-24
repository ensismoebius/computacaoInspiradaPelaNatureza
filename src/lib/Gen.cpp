/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * This class are responsible for handling all methods of genetic algorithms
 * the magic happens inside here ;)
 */

#include <bits/types/FILE.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <stdexcept>

#include "gaussianRandom.h"

#ifndef CLASS_Gen_CPP_
#define CLASS_Gen_CPP_

/**
 * This class are responsible for handling all methods of genetic algorithms
 * the magic happens inside here ;)
 */
class Gen {
	private:

		/**
		 * Contains the file writer
		 */
		FILE* filewriter;

		/**
		 * Hold the best subject score
		 */
		double bestScore;

		/**
		 * Counts the generations
		 */
		unsigned int generation = 0;

		/**
		 * Contains the number of subject bits
		 */
		int subjectSize;

		/**
		 * Contains the number of population bits
		 */
		int populationSize;

		/**
		 * Contains the mutation rate for sexual reproduction
		 */
		double mutationRate;

		/**
		 * Contains the crossover rate for sexual reproduction
		 */
		double crossoverRate;

		/**
		 * This is how much the fitness must influence
		 * in the selection of the subjects
		 */
		double fitnessWeight;

		/**
		 * This is how much the diversity must influence
		 * in the selection of the subjects
		 */
		double diversityWeight;

		/**
		 * Its here where the folks live
		 */
		char* arrPopulation; // TODO use an binary tree here

		/**
		 * Put the babies here!!
		 */
		char* arrNewPopulation; // TODO use an binary tree here

		/**
		 * Holds the indexes of who will have sex tonight!!
		 */
		int* arrBreedersIndexes;

		/**
		 * Holds the values of fitness of the
		 * current populations after evaluation
		 */
		double* arrFitness;

		/**
		 * Holds the values of ranking spaced fitness of the
		 * current populations after evaluation
		 */
		double* arrRankingSpaceFitness;

		/**
		 * Here we puts the gametes of
		 * the most adapted subjects
		 * (one at a time)
		 */
		char* rnaBest1;

		/**
		 * Here we puts the gametes of
		 * the most adapted subjects
		 * (one at a time)
		 */
		char* rnaBest2;

		/**
		 * Here we puts the gametes of
		 * the most diverse subjects
		 * (one at a time)
		 */
		char* rnaSpcR1;

		/**
		 * Here we puts the gametes of
		 * the most diverse subjects
		 * (one at a time)
		 */
		char* rnaSpcR2;

		/**
		 * Here we puts the gametes of
		 * the most anyone
		 * (one at a time)
		 */
		char* anyoneRna1;

		/**
		 * Here we puts the gametes of
		 * the most anyone
		 * (one at a time)
		 */
		char* anyoneRna2;

		/**
		 * Here we puts the gametes of
		 * the most ugly subjects.
		 * (one at a time)
		 *
		 * Because in this society
		 * it is beautiful to be ugly!!
		 */
		char* worseBreederRna1;

		/**
		 * Here we puts the gametes of
		 * the most ugly subjects.
		 * (one at a time)
		 *
		 * Because in this society
		 * it is beautiful to be ugly!!
		 */
		char* worseBreederRna2;

		/**
		 * Pointer for external fitness functions
		 * it varies according to problem
		 * @param arrSubject - subject genotype (ones an zeros)
		 * @param subjectSize
		 * @return fitness value (the less the better!!!)
		 */
		double (*fitnessFunction)(char* arrSubject, int subjectSize);

		/**
		 * Pointer for external initial population
		 * generator functions
		 * @param arrPopulation - Put population here!!!
		 * @param populationSize
		 * @param subjectSize
		 */
		void (*genesisFunction)(char* arrPopulation, int populationSize, int subjectSize);

		/**
		 * Pointer for external a function
		 * whose objective is to print data
		 * in console
		 * @param arrPopulation
		 * @param populationSize
		 * @param subjectSize
		 * @param generation
		 * @param bestScore
		 */
		void (*printFunction)(char* arrPopulation, int populationSize, int subjectSize, int generation, double bestScore);

		/**
		 * The position of best breeder in to arrFitness vector
		 */
		static const unsigned int bestBreederIndex = 0;

		/**
		 * The position of worse breeder in to arrFitness vector
		 */
		static const unsigned int worseBreederIndex = 2;

		/**
		 * The position of best breeder in to arrRankingSpaceFitness vector
		 */
		static const unsigned int bestRankSpacedBreederIndex = 1;

		/**
		 *
		 * Calls the external genesis function
		 * @param arrPopulation
		 */
		void createPopulation(char* arrPopulation) {
			(*this->genesisFunction)(arrPopulation, this->populationSize, this->subjectSize);
		}

		/**
		 * Calls the external fitness function
		 * @param arrSubject
		 * @return
		 */
		double calculateIndividualFitness(char* arrSubject) {
			return (*this->fitnessFunction)(arrSubject, this->subjectSize);
		}

		/**
		 * Calculates the ranking space
		 * fitness of a subject
		 * @param populationIndex
		 * @param diversity
		 * @return
		 */
		double calculateRankingSpaceFitness(int populationIndex, double diversity) {
			return diversity * this->diversityWeight + this->arrFitness[populationIndex] + this->fitnessWeight;
		}

		/**
		 * Self explanatory
		 * @param arrSource
		 * @param arrDestiny
		 * @param size
		 */
		void copyOneArrayToAnother(char* arrSource, char* arrDestiny, int size) {
			while (size--)
				arrDestiny[size] = arrSource[size];
		}

		/**
		 * Given two RNAs crossover them at random positions
		 * @param rna1
		 * @param rna2
		 */
		void doCrossOver(char* rna1, char* rna2) {
			char* mask = this->createRandomMask(this->subjectSize / 2);
			for (int i = 0; i < this->subjectSize / 2; i++) {
				char tmp;
				if (mask[i] == 1) {
					tmp = rna1[i];
					rna1[i] = rna2[i];
					rna2[i] = tmp;
				}
			}

			delete[] mask;
		}

		/**
		 * Given two RNAs mutates them at random positions
		 * @param rna1
		 * @param rna2
		 */
		void mutate(char* rna1, char* rna2) {
			int rnaLocusIndex;
			int amountOfMutations = this->createRandomNumber() * 10;

			while (amountOfMutations--) {
				rnaLocusIndex = this->createRandomNumber() * this->subjectSize / 2;
				rna1[rnaLocusIndex] = rna1[rnaLocusIndex] == 0 ? 1 : 0;
				rnaLocusIndex = this->createRandomNumber() * this->subjectSize / 2;
				rna2[rnaLocusIndex] = rna2[rnaLocusIndex] == 0 ? 1 : 0;
			}
		}

		/**
		 * Extract the RNA for reproduction
		 * @param arrRna - Put RNA here!!
		 * @param subject
		 * @param chainNumber - the index of the DNA helix ( 1 DNA = 2 RNAs ), 0=helix one, 1=helix two
		 */
		void extractRNA(char* arrRna, char* subject, char chainNumber) {
			if (chainNumber < 0 || chainNumber > 1) {
				throw std::invalid_argument("chainNumber must be 0 or 1");
			}

			int rnaIndex = 0;

			for (int i = chainNumber; i < this->subjectSize; i += 2) {
				arrRna[rnaIndex++] = subject[i];
			}
		}

		/**
		 * Retrieves a random number
		 * @return
		 */
		double createRandomNumber() {
			return getUniformDistributedRandomPertubation() / (double) RAND_MAX;
		}

		/**
		 * Create a random binary mask
		 * @param size - size of mask
		 * @return
		 */
		char* createRandomMask(int size) {
			char* mask = new char[size];

			while (size--) {
				mask[size] = createRandomNumber() >= 0.49 ? 1 : 0;
			}

			return mask;
		}

		/**
		 * Sex results in babies!!!
		 * Creates a new subject.
		 * @param arrPopulation
		 * @param rna1
		 * @param rna2
		 */
		void createNewSubject(char* arrPopulation, char* rna1, char* rna2) {
			// crossing over
			if (this->createRandomNumber() <= this->crossoverRate) {
				this->doCrossOver(rna1, rna2);
			}

			// mutation
			if (this->createRandomNumber() <= this->mutationRate) {
				this->mutate(rna1, rna2);
			}

			for (int i = 0; i < this->subjectSize / 2; i++) {
				arrPopulation[i * 2] = rna1[i];
				arrPopulation[i * 2 + 1] = rna2[i];
			}
		}

		/**
		 * The best adapted may live more them non adapted!!!
		 * We must copy some of them so we do not lose their
		 * valuable genotype
		 * @param newPopulationIndex
		 * @param arrNewPopulation
		 */
		void createBestAdaptedCopies(int* newPopulationIndex, char* arrNewPopulation) {
			// 12.5% of population are copies of the best adapted
			// we must maintain breedersIndex at 0
			while (*newPopulationIndex <= this->populationSize / 8.0) {

				int bestBreederLocusIndex;
				int newPopulationLocusIndex;

				for (int i = 0; i < this->subjectSize; i++) {
					bestBreederLocusIndex = this->arrBreedersIndexes[Gen::bestBreederIndex] * this->subjectSize + i;
					newPopulationLocusIndex = (*newPopulationIndex) * this->subjectSize + i;
					arrNewPopulation[newPopulationLocusIndex] = this->arrPopulation[bestBreederLocusIndex];
				}
				(*newPopulationIndex)++;
			}
		}

		/**
		 * Sex time!!! The best ones must
		 * exchange your gametes!!!
		 * @param newPopulationIndex
		 * @param newPopulation
		 */
		void makeBestsHaveSex(int* newPopulationIndex, char* newPopulation) {
			// another 12.5% of population are children from the best adapted
			// and the best space ranked
			int bestBreederIndex = this->arrBreedersIndexes[Gen::bestBreederIndex] * this->subjectSize;
			int spaceRankedIndex = this->arrBreedersIndexes[Gen::bestRankSpacedBreederIndex] * this->subjectSize;

			// extract 1st and 2nd RNA from best adapted
			extractRNA(this->rnaBest1, this->arrPopulation + bestBreederIndex, 0);
			extractRNA(this->rnaBest2, this->arrPopulation + bestBreederIndex, 1);

			// extract 2nd RNA from best space ranked
			extractRNA(this->rnaSpcR1, this->arrPopulation + spaceRankedIndex, 0);
			extractRNA(this->rnaSpcR2, this->arrPopulation + spaceRankedIndex, 1);

			while (*newPopulationIndex <= this->populationSize / 4.0) {

				createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rnaBest1, rnaSpcR1);
				(*newPopulationIndex)++;

				createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rnaBest2, rnaSpcR2);
				(*newPopulationIndex)++;
			}
		}

		/**
		 * Sex time!!! The ugly one have to
		 * exchange your gametes too!!!
		 * @param newPopulationIndex
		 * @param newPopulation
		 */
		void makeWorseHaveSex(int* newPopulationIndex, char* newPopulation) {

			int subjectIndex = -1;

			// extract 1st and 2nd RNA from best adapted
			int worseBreederIndex = this->arrBreedersIndexes[Gen::worseBreederIndex] * this->subjectSize;
			extractRNA(this->worseBreederRna1, this->arrPopulation + worseBreederIndex, 0);
			extractRNA(this->worseBreederRna2, this->arrPopulation + worseBreederIndex, 1);

			while (*newPopulationIndex < this->populationSize) {

				subjectIndex++;

				if (subjectIndex == this->arrBreedersIndexes[Gen::bestBreederIndex]) continue;
				if (subjectIndex == this->arrBreedersIndexes[Gen::worseBreederIndex]) continue;
				if (subjectIndex == this->arrBreedersIndexes[Gen::bestRankSpacedBreederIndex]) continue;

				// extract 2nd RNA from best space ranked
				extractRNA(this->anyoneRna1, this->arrPopulation + subjectIndex * this->subjectSize, 0);
				extractRNA(this->anyoneRna2, this->arrPopulation + subjectIndex * this->subjectSize, 1);

				createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), worseBreederRna1, anyoneRna1);
				(*newPopulationIndex)++;

				if (*newPopulationIndex >= this->populationSize) break;

				createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), worseBreederRna2, anyoneRna2);
				(*newPopulationIndex)++;

			}

		}

		/**
		 * Saves all subject data into a text file
		 * @param arrGenotype
		 * @param fenotype
		 */
		void writeGenotypeFenotype(char *arrGenotype, double fenotype) {

			char strGenotype[this->subjectSize + 1];

			// converts literals values into a readable format
			for (int i = 0; i < this->subjectSize; i++)
				strGenotype[i] = arrGenotype[i] + 48;

			// finalizes the string
			strGenotype[this->subjectSize] = '\0';

			fprintf(this->filewriter, "%i\t%f\t%*s\n", this->generation, fenotype, this->subjectSize, strGenotype);
		}

	public:
		/**
		 * Habemus the constructor!
		 * @param subjectSize - The size the subjects will have
		 * @param populationSize - The size of population
		 * @param fitnessWeight - The influence of fitness in selection
		 * @param diversityWeight - The influence of diversity in selection
		 * @param crossoverRate - Crossover rate
		 * @param mutationRate - Mutation rate
		 * @param fitnessFunction - Pointer to fitness function
		 * @param printFunction - Pointer to print function
		 * @param genesisFunction - Pointer to initial population generator function
		 */
		Gen(int subjectSize, int populationSize, double fitnessWeight, double diversityWeight, double crossoverRate, double mutationRate, double (*fitnessFunction)(char*, int), void (*printFunction)(char* arrPopulation, int populationSize, int subjectSize, int generation, double bestScore), void (*genesisFunction)(char* arrPopulation, int populationSize, int subjectSize)) {

			if (populationSize < 4 || subjectSize < 2 || fitnessWeight <= 0 || diversityWeight <= 0 || crossoverRate > 1 || fitnessFunction == NULL) {
				throw std::invalid_argument("must subjectSize > 1 \n must populationSize > 3 \n must fitnessWeight > 0 \n must diversityWeight > 0\n must crossoverRate < 1\n fitnessFunction != NULL \n ");
			}

			this->generation = 0;

			this->mutationRate = mutationRate;
			this->crossoverRate = crossoverRate;

			//Subject size and population size used to calculate the array sizes
			this->subjectSize = subjectSize;
			this->populationSize = populationSize;

			// The functions
			this->printFunction = printFunction;
			this->fitnessFunction = fitnessFunction;
			this->genesisFunction = genesisFunction;

			// Set the normalized values
			this->fitnessWeight = fitnessWeight / (fitnessWeight + diversityWeight);
			this->diversityWeight = diversityWeight / (fitnessWeight + diversityWeight);

			// People are here
			this->arrFitness = new double[populationSize];
			this->arrBreedersIndexes = new int[populationSize / 2];
			this->arrRankingSpaceFitness = new double[populationSize];

			// Used to store the RNA at time of reproduction
			this->rnaBest1 = new char[this->subjectSize / 2];
			this->rnaBest2 = new char[this->subjectSize / 2];
			this->rnaSpcR1 = new char[this->subjectSize / 2];
			this->rnaSpcR2 = new char[this->subjectSize / 2];
			this->anyoneRna1 = new char[this->subjectSize / 2];
			this->anyoneRna2 = new char[this->subjectSize / 2];
			this->worseBreederRna1 = new char[this->subjectSize / 2];
			this->worseBreederRna2 = new char[this->subjectSize / 2];

			// The best score of generation!! (less is better)
			this->bestScore = std::numeric_limits<double>::max();

			this->arrPopulation = new char[this->populationSize * this->subjectSize];
			this->arrNewPopulation = new char[this->populationSize * this->subjectSize];
			this->createPopulation(this->arrPopulation);
		}

		/**
		 * Destructor
		 */
		~Gen() {

			delete[] this->anyoneRna1;
			delete[] this->anyoneRna2;
			this->anyoneRna1 = NULL;
			this->anyoneRna2 = NULL;

			delete[] this->worseBreederRna1;
			delete[] this->worseBreederRna2;
			this->worseBreederRna1 = NULL;
			this->worseBreederRna2 = NULL;

			delete[] this->rnaBest1;
			delete[] this->rnaBest2;
			delete[] this->rnaSpcR1;
			delete[] this->rnaSpcR2;

			this->rnaBest1 = NULL;
			this->rnaBest2 = NULL;
			this->rnaSpcR1 = NULL;
			this->rnaSpcR2 = NULL;

			delete[] this->arrFitness;
			//delete[] this->arrPopulation;
			delete[] this->arrNewPopulation;
			delete[] this->arrBreedersIndexes;
			delete[] this->arrRankingSpaceFitness;

			this->arrFitness = NULL;
			this->arrPopulation = NULL;
			this->arrNewPopulation = NULL;
			this->arrBreedersIndexes = NULL;
			this->arrRankingSpaceFitness = NULL;
		}

		/**
		 * Its here that the arrFitness and
		 * arrRankingSpaceFitness are filled
		 * evaluates all subjects and give them
		 * some punctuation
		 */
		void evaluateAllSubjects() {

			int index = 0;
			double diversity;
			double sumOfScores = 0;
			double tempScore = 0;
			char sumReachesInfinty = 0;

			// evaluating all subjects
			for (; index < this->populationSize; index++) {
				tempScore = this->arrFitness[index] = this->calculateIndividualFitness(this->arrPopulation + (index * this->subjectSize));

				this->writeGenotypeFenotype(this->arrPopulation + (index * this->subjectSize), tempScore);

				this->bestScore = this->bestScore > tempScore ? tempScore : this->bestScore;
				sumOfScores += tempScore;
			}

			// setting the global score, ideally, in most cases, it has to reach zero
			if (sumOfScores == std::numeric_limits<double>::infinity()) {
				sumOfScores = std::numeric_limits<double>::max();
				sumReachesInfinty = 1;
			}

			// normalizing results
			index--;

			if (sumReachesInfinty) {
				// sumOfAllScores reaching infinity means
				// no fitness, remember the lower the fitness
				// value the better
				for (; index >= 0; index--) {

					if (this->arrFitness[index] == std::numeric_limits<double>::max()) {
						this->arrFitness[index] = 1 / this->populationSize;
						continue;
					}
					this->arrFitness[index] /= std::numeric_limits<double>::max();
				}
			} else {

				// No infinity... that is good!
				for (; index >= 0; index--) {
					this->arrFitness[index] /= sumOfScores;
				}
			}

			// calculating the diversity and raking space fitness
			index++;
			for (; index < this->populationSize; index++) {
				diversity = fabs((1.0 / this->populationSize) - this->arrFitness[index]);
				this->arrRankingSpaceFitness[index] = calculateRankingSpaceFitness(index, diversity);
			}
		}

		/**
		 * Its time to say who will get sex and who does not.
		 * Its here that the arrFitness and
		 * arrRankingSpaceFitness are read and
		 * the arrBreedersIndexes is filled
		 */
		void selectTheBestSubjects() {

			// IMPORTANT the lower the globalScore the better
			int index = 0;

			double worseFitness = 0;
			double bestFitness = std::numeric_limits<double>::max();
			double bestRankingSpaceFitness = std::numeric_limits<double>::max();

			int amountOfSelectedSubjects = 0;

			// finding the best adapted
			for (index = 0; index < this->populationSize; index++) {
				if (this->arrFitness[index] < bestFitness) {
					bestFitness = this->arrFitness[index];
					this->arrBreedersIndexes[Gen::bestBreederIndex] = index;
				}
			}
			amountOfSelectedSubjects++;

			// finding the best ranking spaced
			for (index = 0; index < this->populationSize; index++) {
				// We want another subject then the best adapted
				if (index == this->arrBreedersIndexes[Gen::bestBreederIndex]) continue;

				if (this->arrRankingSpaceFitness[index] < bestRankingSpaceFitness) {
					bestRankingSpaceFitness = this->arrRankingSpaceFitness[index];
					this->arrBreedersIndexes[Gen::bestRankSpacedBreederIndex] = index;
				}
			}
			amountOfSelectedSubjects += abs(bestRankingSpaceFitness) > 0 ? 1 : 0;

			// finding the worse
			for (index = 0; index < this->populationSize; index++) {
				// We want another subject then the others selected
				if (this->arrBreedersIndexes[Gen::bestBreederIndex] == index) continue;
				if (this->arrBreedersIndexes[Gen::bestRankSpacedBreederIndex] == index) continue;

				// finding the worst adapted
				if (this->arrFitness[index] > worseFitness) {
					worseFitness = this->arrFitness[index];
					this->arrBreedersIndexes[Gen::worseBreederIndex] = index;
				}
			}
			amountOfSelectedSubjects += worseFitness != std::numeric_limits<double>::max() ? 1 : 0;

			if (amountOfSelectedSubjects >= this->populationSize / 2) return;

			// selecting another ones...
			for (index = 0; index < this->populationSize; index++) {

				// We want another subject then the others selected
				if (this->arrBreedersIndexes[Gen::bestBreederIndex] == index) continue;
				if (this->arrBreedersIndexes[Gen::worseBreederIndex] == index) continue;
				if (this->arrBreedersIndexes[Gen::bestRankSpacedBreederIndex] == index) continue;

				this->arrBreedersIndexes[amountOfSelectedSubjects] = index;
				amountOfSelectedSubjects++;
				if (amountOfSelectedSubjects == this->populationSize / 2) break;
			}
		}

		/**
		 * Time to born some babies!!!
		 * Here we create a brand new population!!!
		 */
		void createNextGeneration() {
			// This variable are use to control the number of subjects
			int newPopulationIndex = 0;

			// 12.5% of population are copies of the best adapted
			// we must maintain breedersIndex at 0
			createBestAdaptedCopies(&newPopulationIndex, this->arrNewPopulation);

			// another 12.5% of population are children from the best adapted
			// and the best space ranked
			makeBestsHaveSex(&newPopulationIndex, this->arrNewPopulation);

			// another 50% of population are children from worse adapted
			makeWorseHaveSex(&newPopulationIndex, this->arrNewPopulation);

			// Copy new population to regular population
			this->copyOneArrayToAnother(this->arrNewPopulation, this->arrPopulation, populationSize * subjectSize);

			// advances one generation
			this->generation++;
		}

		/*
		 * From now on, all the getter and setters
		 */

		int getPopulationSize() const {
			return populationSize;
		}

		void setPopulationSize(int populationSize) {
			this->populationSize = populationSize;
		}

		int getSubjectSize() const {
			return subjectSize;
		}

		void setSubjectSize(int subjectSize) {
			this->subjectSize = subjectSize;
		}

		double getBestScore() const {
			return bestScore;
		}

		void setGlobalScore(double score = 0) {
			this->bestScore = score;
		}
		void printPopulation() {
			(*this->printFunction)(this->arrPopulation, this->populationSize, this->subjectSize, this->generation, this->bestScore);
		}

		char* getArrPopulation() const {
			return arrPopulation;
		}

		FILE* getFilewriter() {
			return filewriter;
		}

		void setFilewriter(FILE* filewriter) {
			this->filewriter = filewriter;
		}

		unsigned int getGeneration() const {
			return generation;
		}
};

#endif /* CLASS_Gen_CPP_ */

