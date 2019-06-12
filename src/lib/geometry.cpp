/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 11 de jun de 2019
 *
 */
#include <cmath>
long euclidianDistance2d(long* coord1, long* coord2) {
	return sqrt(pow(coord2[0] + coord1[0], 2) + pow(coord2[1] + coord1[1], 2));
}
long euclidianDistance2d(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 + x1, 2) + pow(y2 + y1, 2));
}
