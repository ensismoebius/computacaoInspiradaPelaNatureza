/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 12 de jun de 2019
 *
 */
#ifndef CLASS_ACOExperiment01_CPP_
#define CLASS_ACOExperiment01_CPP_

#include <iostream>

#include "../lib/ACOAnt.cpp"
#include "../lib/ACOMap.cpp"

namespace ACOExperiments {

	class Experiment01 {
		public:
			static void perform() {
				int iterations = 15;
				int amountOfLocations = 52;

				ACOMap::decayRate = 0.1;
				ACOMap::initialWeight = 0.01;
				ACOMap::initialBestWeight = 0.01;

				ACOAnt::weightInfluence = 1;
				ACOAnt::distanceInfluence = 2;
				ACOAnt::weightRate = 0.5;

				ACOMap map(amountOfLocations);
				ACOAnt** ants = new ACOAnt*[amountOfLocations];

				map.addNeighborhood(565.0, 575.0, 0);
				map.addNeighborhood(25.0, 185.0, 1);
				map.addNeighborhood(345.0, 750.0, 2);
				map.addNeighborhood(945.0, 685.0, 3);
				map.addNeighborhood(845.0, 655.0, 4);
				map.addNeighborhood(880.0, 660.0, 5);
				map.addNeighborhood(25.0, 230.0, 6);
				map.addNeighborhood(525.0, 1000.0, 7);
				map.addNeighborhood(580.0, 1175.0, 8);
				map.addNeighborhood(650.0, 1130.0, 9);
				map.addNeighborhood(1605.0, 620.0, 10);
				map.addNeighborhood(1220.0, 580.0, 11);
				map.addNeighborhood(1465.0, 200.0, 12);
				map.addNeighborhood(1530.0, 5.0, 13);
				map.addNeighborhood(845.0, 680.0, 14);
				map.addNeighborhood(725.0, 370.0, 15);
				map.addNeighborhood(145.0, 665.0, 16);
				map.addNeighborhood(415.0, 635.0, 17);
				map.addNeighborhood(510.0, 875.0, 18);
				map.addNeighborhood(560.0, 365.0, 19);
				map.addNeighborhood(300.0, 465.0, 20);
				map.addNeighborhood(520.0, 585.0, 21);
				map.addNeighborhood(480.0, 415.0, 22);
				map.addNeighborhood(835.0, 625.0, 23);
				map.addNeighborhood(975.0, 580.0, 24);
				map.addNeighborhood(1215.0, 245.0, 25);
				map.addNeighborhood(1320.0, 315.0, 26);
				map.addNeighborhood(1250.0, 400.0, 27);
				map.addNeighborhood(660.0, 180.0, 28);
				map.addNeighborhood(410.0, 250.0, 29);
				map.addNeighborhood(420.0, 555.0, 30);
				map.addNeighborhood(575.0, 665.0, 31);
				map.addNeighborhood(1150.0, 1160.0, 32);
				map.addNeighborhood(700.0, 580.0, 33);
				map.addNeighborhood(685.0, 595.0, 34);
				map.addNeighborhood(685.0, 610.0, 35);
				map.addNeighborhood(770.0, 610.0, 36);
				map.addNeighborhood(795.0, 645.0, 37);
				map.addNeighborhood(720.0, 635.0, 38);
				map.addNeighborhood(760.0, 650.0, 39);
				map.addNeighborhood(475.0, 960.0, 40);
				map.addNeighborhood(95.0, 260.0, 41);
				map.addNeighborhood(875.0, 920.0, 42);
				map.addNeighborhood(700.0, 500.0, 43);
				map.addNeighborhood(555.0, 815.0, 44);
				map.addNeighborhood(830.0, 485.0, 45);
				map.addNeighborhood(1170.0, 65.0, 46);
				map.addNeighborhood(830.0, 610.0, 47);
				map.addNeighborhood(605.0, 625.0, 48);
				map.addNeighborhood(595.0, 360.0, 49);
				map.addNeighborhood(1340.0, 725.0, 50);
				map.addNeighborhood(1740.0, 245.0, 51);

				map.traceConnections();

				for (unsigned int pi = 0; pi < map.pointsLentgh; pi++) {
					ants[pi] = new ACOAnt(map.points[pi], map.pointsLentgh);
				}

				while (iterations--) {
					for (unsigned int ai = 0; ai < map.pointsLentgh; ai++) {
						ants[ai]->walk();
					}
					map.decayWeights();
					std::cout << "Remaining iterations: " << iterations << "\n";
				}

				map.saveBestPath(map.points[0], "/tmp/data01.csv");

				openFile("/tmp/p");
				writeCharsToFile("plot \"/tmp/data01.csv\" using 1:2:3:4 with vectors filled head lw 1\n");
				closeFile();
				system("gnuplot -p /tmp/p");

				for (unsigned int pi = 0; pi < map.pointsLentgh; pi++) {
					delete ants[pi];
				}
				delete[] ants;
			}
	};
}
#endif /* CLASS_ACOExperiment01_CPP_ */
