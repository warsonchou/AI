// first choice version
#include "iostream"
#include "algorithm"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
using namespace std;

const int range = 100;

struct queen{
	int x; //position
	int y;
};

void getRandomStart(queen a[]) {
	int i, j, x, y;
	for (i = 0; i < 8; i++) {
		while (1) {
			x = rand() % 8;
			y = rand() % 8;
			for (j = 0; j < 8; j++) {
				if (a[j].x == x && a[j].y == y) {
					break;
				}
			}
			if (j == 8)
				break;
		}
	}
}

bool isReached(queen q[]) {
	int i, j;
	bool isAllSafe = true;
	for (i = 0; i < 8; i++) {
		for (j = i + 1; j < 8; j++) {
			if (q[i].x == q[j].x || q[i].y == q[j].y || (q[i].x - q[i].y == q[j].x - q[j].y) || (q[i].x + q[i].y == q[j].x + q[j].y)) {
				isAllSafe = false;
				break;
			}
		}
	}
	return isAllSafe;
}

int getH(queen q[]) {
	int i, j, sum = 0;
	for (i = 0; i < 8; i++) {
		for (j = i + 1; j < 8; j++) {
			if (q[i].x == q[j].x || q[i].y == q[j].y || (q[i].x - q[i].y == q[j].x - q[j].y) || (q[i].x + q[i].y == q[j].x + q[j].y)) {
				sum++;
			}
		}
	}
	return sum;
}

bool isSafe(queen q[], int targetIndex, int x, int y) {
	bool safe = true;
	int i, j;
	for (i = 0; i < 8; i++) {
		if (q[i].x == x && q[i].y == y) {
			safe = false;
			break;
		}

		for (j = 0; j < 8; j++) {
			if (j == targetIndex)
				continue;
			if (q[j].x == x || q[j].y == y || (q[j].x - q[j].y == x - y) || (q[j].x + q[j].y == x + y)) {
				if ((q[i].x > q[j].x && q[j].x > x) || (q[i].x < q[j].x && q[j].x < x)) {
					safe = false;
					break;
				}
			}
		}
	}
	return safe;
}

bool move(queen a[], int &bestH, bool isFoundEqual) {
	int i, j, h;
	queen temp;
	bool isFoundbetter = false;
	for (i = 0; i < 8; i++) {
		// 左移动
		for (j = 1; j < 8; j++) {
			if(a[i].x - j >= 0 && isSafe(a, i, a[i].x - j, a[i].y))  {
				temp.x = a[i].x;
				a[i].x -= j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}

				a[i].x = temp.x;
			} 
		}
		if (isFoundbetter)
			break;

		// 右移动
		for (j = 1; j < 8; j++) {
			if(a[i].x + j < 8 && isSafe(a, i, a[i].x + j, a[i].y))  {
				temp.x = a[i].x;
				a[i].x += j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].x = temp.x;
			} 
		}
		if (isFoundbetter)
			break;

		// 上移
		for (j = 1; j < 8; j++) {
			if(a[i].y - j >= 0 && isSafe(a, i, a[i].x, a[i].y - j))  {
				temp.y = a[i].y;
				a[i].y -= j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
			} 
		}
		if (isFoundbetter)
			break;

		// 右移动
		for (j = 1; j < 8; j++) {
			if(a[i].y + j < 8 && isSafe(a, i, a[i].x, a[i].y + j))  {
				temp.y = a[i].y;
				a[i].y += j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
			} 
		}
		if (isFoundbetter)
			break;

		// 左上移动
		for (j = 1; j < 8; j++) {
			if (a[i].x - j >= 0 && a[i].y - j >= 0 && isSafe(a, i, a[i].x - j, a[i].y - j)) {
				temp.x = a[i].x;
				temp.y = a[i].y;
				a[i].x -= j;
				a[i].y -= j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
				a[i].x = temp.x;
			}
		}
		if (isFoundbetter)
			break;

		// 右下移动
		for (j = 1; j < 8; j++) {
			if (a[i].x + j < 8 && a[i].y + j < 8 && isSafe(a, i, a[i].x + j, a[i].y + j)) {
				temp.x = a[i].x;
				temp.y = a[i].y;
				a[i].x += j;
				a[i].y += j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
				a[i].x = temp.x;
			}
		}
		if (isFoundbetter)
			break;

		// 右上角
		for (j = 1; j < 8; j++) {
			if (a[i].x + j < 8 && a[i].y - j >= 0 && isSafe(a, i, a[i].x + j, a[i].y - j)) {
				temp.x = a[i].x;
				temp.y = a[i].y;
				a[i].x += j;
				a[i].y -= j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
				a[i].x = temp.x;
			}
		}
		if (isFoundbetter)
			break;

		// 左下
		for (j = 1; j < 8; j++) {
			if (a[i].x - j >= 0 && a[i].y + j < 8 && isSafe(a, i, a[i].x - j, a[i].y + j)) {
				temp.x = a[i].x;
				temp.y = a[i].y;
				a[i].x -= j;
				a[i].y += j;
				h = getH(a);
				if (h < bestH) {
					bestH = h;
					isFoundbetter = true;
					break;
				}
				if (isFoundEqual && h == bestH) {
					break;
				}
				a[i].y = temp.y;
				a[i].x = temp.x;
			}
		}
	}
	return isFoundbetter;
}

bool RandomStart(queen a[]) {
	int i, j, h, count, loops, currentH, bestH;
	queen temp;
	

	currentH = getH(a);
	bestH = currentH;
	count = 10;
	for (loops = 0; loops < 10000; loops++) {
		
		move(a, bestH, false);

		if (isReached(a))
			return true;

		if (bestH == currentH) {
			// return false;
			for (int g = 0; g < range; g++) {
				if (move(a, bestH, true)) {
					currentH = bestH;
					break;
				}
			}
			if(bestH == currentH) {
				if (count == 0) {
					return false;
				} else {
					count--;
					getRandomStart(a);
					loops = 0;
				}
			}

		} else {
			currentH = bestH;
		}
	}
	return false;
}

int main(int argc, char const *argv[])
{
	int i, j, k, count = 0;
	queen a[8], test[8], test1[8], q[8];
	

	while(cin >> a[0].x) {
		cin >> a[0].y;
		for (i = 1; i < 8; i++) {
			cin >> a[i].x >> a[i].y;
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl;
		if (RandomStart(a)) {
			count++;
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl << endl;
	}
	cout << "RandomStart HillClimb algorithm in solving the 8-queen problem:\nSolved percentage: ";
	cout << ((double)count / (double)10000 * (double)100) << "%" << endl;
	return 0;
}