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

#include "lib/SquareMatrix.cpp"

int main() {

	SquareMatrix<double, 20, 10> arr;

	arr.set(10, 0, 0, 0);
	arr.set(20, 1, 0, 1);
	arr.set(30, 0, 1, 1);
	arr.set(40, 1, 1, 2);

	return 0;
}
