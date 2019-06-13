/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 8 de jun de 2019
 *
 */

#include "ACOMap.cpp"
#include "Ant.cpp"
int main() {

	ACOMap map(6);

	map.addNeighborhood(1, 1, 0);
	map.addNeighborhood(10, 1, 1);
	map.addNeighborhood(10, 10, 2);
	map.addNeighborhood(1, 10, 3);
	map.addNeighborhood(5, 15, 4);
	map.addNeighborhood(5, 5, 5);

	map.traceConnections();
//	map.printAll();

	Ant** ants = new Ant*[6];

	for (unsigned int pi = 0; pi < map.pointsLentgh; pi++) {
		ants[pi] = new Ant(map.points[pi], map.pointsLentgh);
	}

	int iterations = 100;

	while (iterations--) {
		for (unsigned int ai = 0; ai < map.pointsLentgh; ai++) {
			ants[ai]->walk();
		}
		map.decayWeights();
	}

	map.printBestPath(map.points[0]);

	return 0;
}
