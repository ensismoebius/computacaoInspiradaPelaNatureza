/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 */

#include <cstdlib>
#include <limits>
#include <stdexcept>

class Gen {
private:
	int subjectSize;
	int populationSize;

	double mutationRate;
	double crossoverRate;

	double fitnessWeight;
	double diversityWeight;

	// TODO use an binary tree here
	int* arrBreeders;
	char* arrPopulation;

	// TODO use an binary tree here
	double* arrFitness;
	double* arrRankingSpaceFitness;

	const char targetSubject[12] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 };

	static const unsigned int bestBreederIndex = 0;
	static const unsigned int worseBreederIndex = 2;
	static const unsigned int bestRankSpacedBreederIndex = 1;

	int calculateIndividualFitness(char* arrSubject) {
		int score = 0;
		int index = this->subjectSize;

		while (index--) {
			score += arrSubject[index] == this->targetSubject[index] ? 1 : 0;
		}

		return score;
	}

	double calculateRankingSpaceFitness(int populationIndex, double diversity) {
		return diversity * this->diversityWeight + this->arrFitness[populationIndex] + this->fitnessWeight;
	}

	char *createPopulation() {
		int genesAmount = this->populationSize * this->subjectSize;
		char* population = new char[genesAmount];

		// initializes the population
		while (genesAmount--) {
			population[genesAmount] = random() > RAND_MAX / 2 ? 1 : 0;
		}

		return population;
	}

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
	}

	void mutate(char* rna1, char* rna2) {
		int rnaLocusIndex;
		rnaLocusIndex = this->createRandomNumber() * this->subjectSize / 2;
		rna1[rnaLocusIndex] = rna1[rnaLocusIndex] == 0 ? 1 : 0;
		rnaLocusIndex = this->createRandomNumber() * this->subjectSize / 2;
		rna2[rnaLocusIndex] = rna1[rnaLocusIndex] == 0 ? 1 : 0;
	}

	char* extractRNA(char* subject, char chainNumber) {
		if (chainNumber < 0 || chainNumber > 1) {
			throw std::invalid_argument("chainNumber must be 0 or 1");
		}

		int rnaIndex = 0;
		char* rna = new char[this->subjectSize / 2];

		for (int i = chainNumber; i < this->subjectSize; i += 2) {
			rna[rnaIndex++] = subject[i];
		}

		return rna;
	}

	double createRandomNumber() {
		return random() / (double) RAND_MAX;
	}

	char* createRandomMask(int size) {
		char* mask = new char[size];

		while (size--) {
			mask[size] = createRandomNumber() >= 0.49 ? 1 : 0;
		}

		return mask;
	}

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

	void createBestAdaptedCopies(int* newPopulationIndex, char* arrNewPopulation) {
		// 12.5% of population are copies of the best adapted
		// we must maintain breedersIndex at 0
		while (*newPopulationIndex <= this->populationSize / 8.0) {

			int bestBreederLocusIndex;
			int newPopulationLocusIndex;

			for (int i = 0; i < this->subjectSize; i++) {
				bestBreederLocusIndex = this->arrBreeders[Gen::bestBreederIndex] * this->subjectSize + i;
				newPopulationLocusIndex = (*newPopulationIndex) * this->subjectSize + i;
				arrNewPopulation[newPopulationLocusIndex] = this->arrPopulation[bestBreederLocusIndex];
			}
			(*newPopulationIndex)++;
		}
	}

	void makeBestsHaveSex(int* newPopulationIndex, char* newPopulation) {
		// another 12.5% of population are children from the best adapted
		// and the best space ranked
		int bestBreederIndex = this->arrBreeders[Gen::bestBreederIndex] * this->subjectSize;
		int spaceRankedIndex = this->arrBreeders[Gen::bestRankSpacedBreederIndex] * this->subjectSize;

		// extract 1st and 2nd RNA from best adapted
		char* rnaBest1 = extractRNA(this->arrPopulation + bestBreederIndex, 0);
		char* rnaBest2 = extractRNA(this->arrPopulation + bestBreederIndex, 1);

		// extract 2nd RNA from best space ranked
		char* rnaSpcR1 = extractRNA(this->arrPopulation + spaceRankedIndex, 0);
		char* rnaScpR2 = extractRNA(this->arrPopulation + spaceRankedIndex, 1);

		while (*newPopulationIndex <= this->populationSize / 4.0) {

			createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rnaBest1, rnaSpcR1);
			(*newPopulationIndex)++;

			createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rnaBest2, rnaScpR2);
			(*newPopulationIndex)++;
		}
	}

	void makeWorseHaveSex(int* newPopulationIndex, char* newPopulation) {

		int subjectIndex = 0;

		// extract 1st and 2nd RNA from best adapted
		int worseBreederIndex = this->arrBreeders[Gen::worseBreederIndex] * this->subjectSize;
		char* rna11 = extractRNA(this->arrPopulation + worseBreederIndex, 0);
		char* rna12 = extractRNA(this->arrPopulation + worseBreederIndex, 1);

		while (*newPopulationIndex < this->populationSize) {

			if (subjectIndex == this->arrBreeders[Gen::bestBreederIndex]) continue;
			if (subjectIndex == this->arrBreeders[Gen::worseBreederIndex]) continue;
			if (subjectIndex == this->arrBreeders[Gen::bestRankSpacedBreederIndex]) continue;

			// extract 2nd RNA from best space ranked
			char* rna21 = extractRNA(this->arrPopulation + subjectIndex + this->subjectSize, 0);
			char* rna22 = extractRNA(this->arrPopulation + subjectIndex + this->subjectSize, 1);

			createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rna11, rna21);
			(*newPopulationIndex)++;

			createNewSubject(newPopulation + ((*newPopulationIndex) * this->subjectSize), rna12, rna22);
			(*newPopulationIndex)++;

			subjectIndex++;
		}
	}

public:
	Gen(int subjectSize, int populationSize, double fitnessWeight, double diversityWeight, double crossoverRate, double mutationRate) {

		if (populationSize < 4 || subjectSize < 2 || fitnessWeight <= 0 || diversityWeight <= 0 || crossoverRate > 1) {
			throw std::invalid_argument("must subjectSize > 1 \n must populationSize > 3 \n must fitnessWeight > 0 \n must diversityWeight > 0\n must crossoverRate < 1\n");
		}

		this->mutationRate = mutationRate;
		this->crossoverRate = crossoverRate;

		//Subject size and population size to calculate the array sizes
		this->subjectSize = subjectSize;
		this->populationSize = populationSize;

		// Set the normalized values
		this->fitnessWeight = fitnessWeight / (fitnessWeight + diversityWeight);
		this->diversityWeight = diversityWeight / (fitnessWeight + diversityWeight);

		this->arrFitness = new double[populationSize];
		this->arrBreeders = new int[populationSize / 2];
		this->arrRankingSpaceFitness = new double[populationSize];

		this->arrPopulation = createPopulation();
	}

	~Gen() {
		delete[] this->arrFitness;
		delete[] this->arrPopulation;
		delete[] this->arrRankingSpaceFitness;
	}

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

	void evaluateAllSubjects() {

		int index = 0;
		int sumOfAllScores = 0;
		double diversity;

		// evaluating all subjects
		for (; index < this->populationSize; index++) {
			sumOfAllScores += this->arrFitness[index] = this->calculateIndividualFitness(this->arrPopulation + (index * this->subjectSize));
		}

		// normalizing results
		index--;
		for (; index >= 0; index--) {
			this->arrFitness[index] /= sumOfAllScores;
		}

		// calculating the diversity and raking space fitness
		index++;
		for (; index < this->populationSize; index++) {
			diversity = 1.0 / this->populationSize / this->arrFitness[index];
			this->arrRankingSpaceFitness[index] = calculateRankingSpaceFitness(index, diversity);
		}
	}

	void selectTheBestSubjects() {

		int index = 0;

		double bestFitness = 0;
		double worseFitness = std::numeric_limits<double>::max();
		double bestRankingSpaceFitness = 0;

		int amountOfSelectedSubjects = 0;

		// finding the best adapted
		for (index = 0; index < this->populationSize; index++) {
			if (this->arrFitness[index] > bestFitness) {
				bestFitness = this->arrFitness[index];
				this->arrBreeders[Gen::bestBreederIndex] = index;
			}
		}
		amountOfSelectedSubjects++;

		// finding the best ranking spaced
		for (index = 0; index < this->populationSize; index++) {
			// We want another subject then the best adapted
			if (index == this->arrBreeders[Gen::bestBreederIndex]) continue;

			if (this->arrRankingSpaceFitness[index] > bestRankingSpaceFitness) {
				bestRankingSpaceFitness = this->arrRankingSpaceFitness[index];
				this->arrBreeders[Gen::bestRankSpacedBreederIndex] = index;
			}
		}
		amountOfSelectedSubjects += abs(bestRankingSpaceFitness) > 0 ? 1 : 0;

		// finding the worse
		for (index = 0; index < this->populationSize; index++) {
			// We want another subject then the others selected
			if (this->arrBreeders[Gen::bestBreederIndex] == index) continue;
			if (this->arrBreeders[Gen::bestRankSpacedBreederIndex] == index) continue;

			// finding the worst adapted
			if (this->arrFitness[index] < worseFitness) {
				worseFitness = this->arrFitness[index];
				this->arrBreeders[Gen::worseBreederIndex] = index;
			}
		}
		amountOfSelectedSubjects += worseFitness != std::numeric_limits<double>::max() ? 1 : 0;

		if (amountOfSelectedSubjects >= this->populationSize / 2) return;

		// selecting another ones...
		double worseFitnessValue = this->arrFitness[this->arrBreeders[Gen::worseBreederIndex]];
		for (index = 0; index < this->populationSize; index++) {

			// We want another subject then the others selected
			if (this->arrBreeders[Gen::bestBreederIndex] == index) continue;
			if (this->arrBreeders[Gen::bestRankSpacedBreederIndex] == index) continue;

			// we catch any other that is better than the worse
			if (this->arrFitness[index] < worseFitnessValue) continue;

			this->arrBreeders[amountOfSelectedSubjects] = index;
			amountOfSelectedSubjects++;

			if (amountOfSelectedSubjects == this->populationSize / 2) {
				break;
			}
		}
	}

	void reproduce() {

		int newPopulationIndex = 0;
		char* arrNewPopulation = new char[this->populationSize * this->subjectSize];

		// 12.5% of population are copies of the best adapted
		// we must maintain breedersIndex at 0
		createBestAdaptedCopies(&newPopulationIndex, arrNewPopulation);

		// another 12.5% of population are children from the best adapted
		// and the best space ranked
		makeBestsHaveSex(&newPopulationIndex, arrNewPopulation);

		// another 50% of population are children from worse adapted
		makeWorseHaveSex(&newPopulationIndex, arrNewPopulation);

	}
};

int main() {

	// represents a matrix of 3x4
	//	0, 1, 0,
	//	0, 1, 0,
	//	0, 1, 0,
	//	0, 1, 0,
	Gen pop = Gen(12, 4, 8, 2, 0.8, 0.001);
	pop.evaluateAllSubjects();
	pop.selectTheBestSubjects();
	pop.reproduce();
	return 0;
}
