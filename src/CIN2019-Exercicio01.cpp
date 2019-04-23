#include "hillClimbingAnnealingExperiments/Experiment01.cpp"
#include "hillClimbingAnnealingExperiments/Experiment02.cpp"
#include "hillClimbingAnnealingExperiments/Experiment03.cpp"
#include "hillClimbingAnnealingExperiments/Experiment04.cpp"

#include "geneticExperiments/Experiment01.cpp"
#include "geneticExperiments/Experiment02.cpp"
#include "geneticExperiments/Experiment03.cpp"
#include "geneticExperiments/Experiment04.cpp"

int main() {

	geneticExperiments::Experiment01::perform(1000,"/tmp/geneticExperiments::Experiment01.csv");
	geneticExperiments::Experiment02::perform(1000,"/tmp/geneticExperiments::Experiment02.csv");
	geneticExperiments::Experiment03::perform(1000,"/tmp/geneticExperiments::Experiment03.csv");
	geneticExperiments::Experiment04::perform(1000,"/tmp/geneticExperiments::Experiment04.csv");

	// hill climbing algorithms
	hillClimbingAnnealingExperiments::Experiment01::perform(1000,"/tmp/hillClimbingAnnealingExperiments::Experiment01.csv");
	hillClimbingAnnealingExperiments::Experiment02::perform(1000,"/tmp/hillClimbingAnnealingExperiments::Experiment02.csv");
	hillClimbingAnnealingExperiments::Experiment03::perform(1000,"/tmp/hillClimbingAnnealingExperiments::Experiment03.csv");

	// annealing algorithms
	hillClimbingAnnealingExperiments::Experiment04::perform(1000,"/tmp/hillClimbingAnnealingExperiments::Experiment04.csv");

	return 0;
}

