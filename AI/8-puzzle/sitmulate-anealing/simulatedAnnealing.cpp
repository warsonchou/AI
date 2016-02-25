// 退火算法。
#include "iostream"
#include "algorithm"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
using namespace std;

const double coolingRate = 0.99999;
const double minT        = pow(10, -6);
const double initialT    = pow(10, 4);
const double equalDis    = pow(10, -4);

void getRandomStart(int a[3][3]) {
	int i, j, num;
	bool isPut[9];
	memset(isPut, false, sizeof(isPut));
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			while(1) {
				srand((unsigned) time(NULL)); 
				num = rand() % 9;
				if (isPut[num]) {
					continue;
				} else {
					isPut[num] = true;
					a[i][j] = num + 1;
					break;
				}
			}
		}
	}
}

bool isReached(int a[3][3]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (a[i][j] != i * 3 + j + 1)
				break;
		}
	}
	return (i == 3 && j == 3);
}

int getDistance(int target, int x, int y) {
	int shouldX = target / 3 + 1, shouldY = target % 3;
	if (shouldY == 0) {
		shouldX--;
		shouldY = 3;
	}
	return (abs(shouldX - x) + abs(shouldY - y));
}

int getH(int a[3][3]) {
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (a[i][j] == 9)
				continue;
			sum += getDistance(a[i][j], i + 1, j + 1);
			// cout << a[i][j] << " " << i << " " << j << " " << getDistance(a[i][j], i + 1, j + 1) << endl;
		}
	}
	return sum;
}

int getRandomSuccessor(int x, int y) {
	int dirx[4] = {0, 0, 1, -1}, diry[4] ={1, -1, 0, 0}, num = rand() % 4;
	while (1) {
		if (x + dirx[num] >= 0 && x + dirx[num] < 3 && y + diry[num] >= 0 && y + diry[num] < 3)
			break;
		num++;
		num %= 4;
	}
	return num;
}

bool acceptProbalility(int currentH, int newH, double temperature) {
	if (currentH > newH) {
		return true;
	} else {
		// srand((unsigned) time(NULL)); 
		int randnum = rand() % 1000;
		double currentnum = exp(((double)currentH - (double)newH) / temperature) * (double)1000;
		// cout << randnum<< " " << currentnum << " " << ((int)currentnum > randnum) << " ";
		return ((int)currentnum > randnum);
	}
}

bool simulatedAnnealing(int a[3][3]) {
	int i, j, h, loops, direction, posxofspace, posyofspace, x[4] = {0, 0, 1, -1}, y[4] ={1, -1, 0, 0}, currentH, dh, temp;
	double  tempT;

	// get the position of 9
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (a[i][j] == 9)
				break;
		}
		if (a[i][j] == 9)
			break;
	}
	posxofspace = i;
	posyofspace = j;
	currentH =getH(a);
	// bestH = currentH;
	tempT = initialT;

	while (tempT > minT) {
		direction = getRandomSuccessor(posxofspace, posyofspace);
		// 先交换位置
		temp = a[posxofspace][posyofspace];
		a[posxofspace][posyofspace] = a[posxofspace + x[direction]][posyofspace + y[direction]];
		a[posxofspace + x[direction]][posyofspace + y[direction]] = temp;

		h = getH(a);

		// 得到了最佳解
		if (isReached(a)) {
			currentH = h;
			break;
		}
		if (acceptProbalility(currentH, h, tempT)) {
			// cout << "yes ";
			currentH = h;
			// 接受就交换位置
			posxofspace = posxofspace + x[direction];
			posyofspace = posyofspace + y[direction];
		} else {
			// cout << "no ";
			// 不接受的就交换回来
			temp = a[posxofspace][posyofspace];
			a[posxofspace][posyofspace] = a[posxofspace + x[direction]][posyofspace + y[direction]];
			a[posxofspace + x[direction]][posyofspace + y[direction]] = temp;
		}
		
		tempT *= coolingRate;
	}
	// cout << currentH << endl;
	return (currentH == 0);
}

int main(int argc, char const *argv[])
{
	int i, j, k, count = 0, a[3][3];
	while(cin >> a[0][0]) {
		// getRandomStart(a);
		// cin >> a[0][0];
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (k == 0 && j == 0)
					continue;
				cin >> a[j][k];
			}
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl;
		if (simulatedAnnealing(a)) {
			count++;
		}
		// for (j = 0; j < 3; j++) {
		// 	for (k = 0; k < 3; k++) {
		// 		cout << a[j][k] << " ";
		// 	}
		// }
		// cout << endl << endl;
	}
	cout << "SimulatedAnnealing HillClimb algorithm in solving the 8-puzzle problem:\nSolved percentage: ";
	cout << ((double)count / (double)10000 * (double)100) << "%" << endl;
	return 0;
}

