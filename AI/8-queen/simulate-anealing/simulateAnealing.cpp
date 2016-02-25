// simulate anealing version
#include "iostream"
#include "algorithm"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
using namespace std;

const double coolingRate = 0.99;
const double minT        = pow(10, -6);
const double initialT    = pow(10, 4);
const double equalDis    = pow(10, -4);

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

bool acceptProbalility(int currentH, int newH, double temperature) {
	if (currentH > newH) {
		return true;
	} else {
		int randnum = rand() % 1000;
		double currentnum = exp(((double)currentH - (double)newH) / temperature) * (double)1000;
		return ((int)currentnum > randnum);
	}
}

// void onestep(queen a[], int whichQueen, int &bestH, int x, int y, int temperature) {
// 	int i = whichQueen, j, h = bestH, bestx, besty, currentH = bestH, count;
// 	queen temp;
// 	// srand((unsigned)time(NULL)); 
// 	j = rand() % 7;
// 	count = 0;
// 	// get how far to move
// 	while (1) {
// 		count++;
// 		if(a[i].x + x * j >= 0 && a[i].x + x * j < 8 && a[i].y + y * j >=0 && a[i].y + y * j < 8 && isSafe(a, a[i].x + x * j, a[i].y + y * j)) {
// 			break;
// 		}
// 		if (count == 1000)
// 			break;
// 		j = rand() % 7;
// 	}
// 	if (count == 1000)
// 		return;
// 	temp.x = a[i].x;
// 	temp.y = a[i].y;
// 	a[i].x += x * j;
// 	a[i].y += y * j;
// 	h = getH(a);

// 	if (h < bestH) {
// 		bestH = h;
// 		return;
// 	}

// 	// 接受坏的情况
// 	if (acceptProbalility(bestH, h, temperature)) {
// 		bestH = h;
// 	} else {
// 		a[i].x = temp.x;
// 		a[i].y = temp.y;
// 	}
// }

void move(queen a[], int &bestH, int temperature) {
	int i, j, h = bestH, x, y, currentH = bestH;
	queen temp, best;
	
	while (1) {
		x = rand() % 8;
		y = rand() % 8;
		for (i = 0; i < 8; i++) {
			if (a[i].x == x && a[i].y == y) {
				break;
			}
		}
		if (i == 8) {
			break;
		}
	}
	while (1) {
		i = rand() % 8;
		if ((a[i].x == x || a[i].y == y || (a[i].x - a[i].y == x - y) || (a[i].x + a[i].y == x + y)) && isSafe(a, i, x, y)) {
			temp.x = a[i].x;
			temp.y = a[i].y;
			a[i].x = x;
			a[i].y = y;
			h = getH(a);
			break;
		}
		break;
	}

	if (h < bestH) {
		bestH = h;
		return;
	}

	if (acceptProbalility(bestH, h, temperature)) {
		bestH = h;
	} else {
		a[i].x = temp.x;
		a[i].y = temp.y;
	}

}

bool simulateAnealing(queen a[]) {
	double tempT = initialT;
	int i, j, h, loops, currentH =getH(a), bestH = currentH;

	while (tempT > minT) {
		if (isReached(a))
			return true;

		move(a, bestH, tempT);
		tempT *= coolingRate;
	}
	return false;
}


int main(int argc, char const *argv[])
{
	int i, j, k, count = 0;
	queen a[8], test[8], test1[8], q[8];
	srand((unsigned)time(0));

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
		if (simulateAnealing(a)) {
			count++;
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl << endl;
	}
	cout << "SimulateAnealing HillClimb algorithm in solving the 8-queen problem:\nSolved percentage: ";
	cout << ((double)count / (double)10000 * (double)100) << "%" << endl;
	return 0;
}