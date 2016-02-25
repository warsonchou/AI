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

void onestep(queen a[], int whichQueen, int &bestH, int x, int y, bool isFoundEqual) {
	int i = whichQueen, j, h = bestH, bestx, besty, currentH = bestH;
	queen temp;
	for (j = 1; j < 8; j++) {
		if(a[i].x + x * j >= 0 && a[i].x + x * j < 8 && a[i].y + y * j >=0 && a[i].y + y * j < 8 && isSafe(a, i, a[i].x + x * j, a[i].y + y * j))  {
			temp.x = a[i].x;
			temp.y = a[i].y;
			a[i].x += x * j;
			a[i].y += y * j;
			h = getH(a);
			if (h < currentH) {
				currentH = h;
				bestx = a[i].x;
				besty = a[i].y;
			}

			if (isFoundEqual && h == currentH) {
				break;
			}

			a[i].x = temp.x;
			a[i].y = temp.y;
		} 
	}
	if (currentH < bestH) {
		a[i].x = bestx;
		a[i].y = besty;
		bestH = currentH;
	}
}

bool move(queen a[], int &bestH, bool isFoundEqual) {
	int i, j, h = bestH, gox, currentH = bestH;
	queen temp, best;
	for (i = 0; i < 8; i++) {
		// 左移动
		onestep(a, i, bestH, -1, 0, isFoundEqual);
		
		// 右移动
		onestep(a, i, bestH, 1, 0, isFoundEqual);
		
		// 上移
		onestep(a, i, bestH, 0, -1, isFoundEqual);

		// 下移动
		onestep(a, i, bestH, 0, 1, isFoundEqual);

		// 左上移动
		onestep(a, i, bestH, -1, -1, isFoundEqual);

		// 右下移动
		onestep(a, i, bestH, 1, 1, isFoundEqual);
		
		// 右上角
		onestep(a, i, bestH, 1, -1, isFoundEqual);

		// 左下
		onestep(a, i, bestH, -1, 1, isFoundEqual);
	}
	return (bestH < currentH);
}

bool hillClimb(queen a[]) {
	int i, j, h, loops, currentH, bestH;
	queen temp;
	

	currentH = getH(a);
	bestH = currentH;

	for (loops = 0; loops < 10000; loops++) {
		
		move(a, bestH, false);

		if (isReached(a))
			return true;

		if (bestH == currentH) {
			// return false;
			for (int g = 0; g < range; g++) {
				if (move(a, bestH, true)) {
					break;
				} 
			}
			if (bestH == currentH) {
				return false;
			} else {
				currentH = bestH;
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
		if (hillClimb(a)) {
			count++;
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl << endl;
	}
	cout << "Steepest HillClimb algorithm in solving the 8-queen problem:\nSolved percentage: ";
	cout << ((double)count / (double)10000 * (double)100) << "%" << endl;
	return 0;
}