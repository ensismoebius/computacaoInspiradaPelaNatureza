#include "geneticExperiments/Experiment01.cpp"
#include "geneticExperiments/Experiment02.cpp"
#include "geneticExperiments/Experiment03.cpp"
#include "geneticExperiments/Experiment04.cpp"

int main() {

	Experiment01::perform(1000);
	Experiment02::perform(1000);
	Experiment03::perform(1000);
	Experiment04::perform(1000);

	return 0;
}

