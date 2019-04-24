/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 24 de abr de 2019
 *
 * This the base class for all genetic experiments
 * all genetic experiments inherit it
 */
#ifndef CLASS_GeneticExperience_CPP_
#define CLASS_GeneticExperience_CPP_

namespace geneticExperiments {

	/**
	 * This the base class for all genetic experiments
	 * all genetic experiments inherit it
	 */
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
