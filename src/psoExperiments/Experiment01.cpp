/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 6 de jun de 2019
 *
 *
 */

#ifndef SRC_PSOEXPERIMENTS_EXPERIMENT01_CPP_
#define SRC_PSOEXPERIMENTS_EXPERIMENT01_CPP_

#include <iomanip>
#include <iostream>
#include <string>

#include "../lib/fileWriter.h"
#include "../lib/PSO.cpp"

namespace PSOExperiments {

	class Experiment01 {

		public:
			static constexpr double minSpeed = -2;
			static constexpr double maxSpeed = 2;

			static constexpr double selfConfidence = 1.55;
			static constexpr double groupConfidence = 2.55;

			static constexpr int amountOfDimensions = 1;
			static constexpr unsigned int amountOfPopulation = 1;

			static double fitnessFunction(double* values, unsigned int valuesSize) {
				return values[valuesSize - 1] * values[valuesSize - 1];
			}

			static void printFunction(double bestResult, double* bestCoordinates, double result, double* coordinates) {

				(void) result;
				(void) coordinates;

				std::cout << "Best value: " << bestResult << std::endl;

				for (unsigned int i = 0; i < amountOfDimensions; i++) {
					std::cout << bestCoordinates[i] << ",";
				}
				std::cout << std::endl;

//				writeNumberToFile(bestResult);
			}

			static void perform() {

				std::string line;
				std::cout << std::fixed;
				std::cout << std::setprecision(6);

//				openFile("/tmp/PSOExperiments_Experiment01.csv");

				PSOLimits* limits = new PSOLimits(amountOfDimensions);
				limits->addLimits(-7, 7);

				PSO* pso = new PSO(fitnessFunction, amountOfPopulation, amountOfDimensions, minSpeed, maxSpeed, selfConfidence, groupConfidence, limits);
				pso->simulate(1000, printFunction);

//				closeFile();
				delete limits;
				delete pso;
			}
	};
}

#endif /* SRC_PSOEXPERIMENTS_EXPERIMENT01_CPP_ */
