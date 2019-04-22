/*
 * GeneticExperience.cpp
 *
 *  Created on: 22 de abr de 2019
 *      Author: ensis
 */
#ifndef CLASS_GeneticExperience_CPP_
#define CLASS_GeneticExperience_CPP_

namespace geneticExperiments {

	class GeneticExperience {
	public:
		static const int subjectSize = 0;
		static const int populationSize = 0;

		static constexpr double fitnessWeight = 8;
		static constexpr double diversityWeight = 2;

		static constexpr double mutationRate = 0.1;
		static constexpr double crossoverRate = 0.4;
	};
}

#endif /* CLASS_GeneticExperience_CPP_ */
