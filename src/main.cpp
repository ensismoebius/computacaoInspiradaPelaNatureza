/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 8 de jun de 2019
 *
 *
 */

#include "ACOMap.cpp"
#include "Ant.cpp"
int main() {

	ACOMap map(14);

	map.addNeighborhood(1, 2, 0);
	map.addNeighborhood(10, 40, 1);
	map.addNeighborhood(20, 2, 2);
	map.addNeighborhood(52, 3, 3);
	map.addNeighborhood(5, 1, 4);
	map.addNeighborhood(15, 25, 5);
	map.addNeighborhood(5, 2, 6);
	map.addNeighborhood(50, 2, 7);

	map.addNeighborhood(2, 2, 8);
	map.addNeighborhood(30, 40, 9);
	map.addNeighborhood(72, 3, 10);
	map.addNeighborhood(8, 1, 11);
	map.addNeighborhood(25, 25, 12);
	map.addNeighborhood(9, 2, 13);

	map.firstSteps();
	map.printAll();
//	map.printConnections();

	Ant** ants = new Ant*[map.pointsLentgh];

	for (unsigned int pi = 0; pi < map.pointsLentgh; pi++) {
		ants[pi] = new Ant(map.points[pi], map.pointsLentgh);
	}

	int iterations = 100;

	while (iterations--) {
		for (unsigned int pi = 0; pi < map.pointsLentgh; pi++) {
			ants[pi]->walk();
		}
		map.decayWeights();
	}

	return 0;
}
