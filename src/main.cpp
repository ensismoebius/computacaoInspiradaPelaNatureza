/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * This is the main file, welcome!
 * Here we perform all experiments.
 *
 * Long life to open source software!
 * Peace, love and anarchism for everyone!!
 */

#include "neuralExperiments/Experiment01.cpp"

#include "geneticExperiments/Experiment01.cpp"
#include "geneticExperiments/Experiment02.cpp"
#include "geneticExperiments/Experiment03.cpp"
#include "geneticExperiments/Experiment04.cpp"

#include "hillClimbingAnnealingExperiments/Experiment01.cpp"
#include "hillClimbingAnnealingExperiments/Experiment02.cpp"
#include "hillClimbingAnnealingExperiments/Experiment03.cpp"
#include "hillClimbingAnnealingExperiments/Experiment04.cpp"
#include "hillClimbingAnnealingExperiments/Experiment05.cpp"

void doGeneticExperiments() {
	// genetic algorithms
	geneticExperiments::Experiment01::perform(10000, "/tmp/geneticExperiments::Experiment01.csv");
	geneticExperiments::Experiment02::perform(10000, "/tmp/geneticExperiments::Experiment02.csv");
	geneticExperiments::Experiment03::perform(10000, "/tmp/geneticExperiments::Experiment03.csv");
	geneticExperiments::Experiment04::perform(10000, "/tmp/geneticExperiments::Experiment04.csv");
}

void doHillClimbingExperiments() {
	// hill climbing algorithms
	hillClimbingAnnealingExperiments::Experiment01::perform(10000, "/tmp/hillClimbingAnnealingExperiments::Experiment01.csv");
	hillClimbingAnnealingExperiments::Experiment02::perform(10000, "/tmp/hillClimbingAnnealingExperiments::Experiment02.csv");
	hillClimbingAnnealingExperiments::Experiment03::perform(10000, "/tmp/hillClimbingAnnealingExperiments::Experiment03.csv");
	hillClimbingAnnealingExperiments::Experiment05::perform(10000, "/tmp/hillClimbingAnnealingExperiments::Experiment05.csv");
}

void doAnnealingExperiments() {
	// annealing algorithms
	hillClimbingAnnealingExperiments::Experiment04::perform(10000, "/tmp/hillClimbingAnnealingExperiments::Experiment04.csv");
}

void doNeuralExperiments() {
	// neural network experiments
	neuralExperiments::Experiment01::perform();
}

/**
 * Do all the experiments!!!!!
 */
int main() {

//	// genetic algorithms
//	doGeneticExperiments();
//	// hill climbing algorithms
//	doHillClimbingExperiments();
//	// annealing algorithms
//	doAnnealingExperiments();

// neural network
	doNeuralExperiments();

	return 0;
}
