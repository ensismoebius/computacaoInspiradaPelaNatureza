#include "hillClimbingAnnealingExperiments/Experiment01.cpp"
#include "hillClimbingAnnealingExperiments/Experiment02.cpp"
#include "hillClimbingAnnealingExperiments/Experiment03.cpp"
#include "hillClimbingAnnealingExperiments/Experiment04.cpp"

#include "geneticExperiments/Experiment01.cpp"
#include "geneticExperiments/Experiment02.cpp"
#include "geneticExperiments/Experiment03.cpp"
#include "geneticExperiments/Experiment04.cpp"

int main() {

	geneticExperiments::Experiment01::perform(1000);
	geneticExperiments::Experiment02::perform(1000);
	geneticExperiments::Experiment03::perform(1000);
	geneticExperiments::Experiment04::perform(1000);

	// hill climbing algorithms
	hillClimbingAnnealingExperiments::Experiment02::perform(1000);
	hillClimbingAnnealingExperiments::Experiment03::perform(1000);

	// annealing algorithms
	hillClimbingAnnealingExperiments::Experiment04::perform(1000);
	return 0;
}

