// 使用曼哈顿距离来到度量好坏
// steeoest-acsent version
#include "iostream"
#include "algorithm"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
using namespace std;

const int range = 100;

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

bool hillClimb(int a[3][3]) {
	int i, j, h, loops, posxofspace, posyofspace, x[4] = {0, 0, 1, -1}, y[4] ={1, -1, 0, 0}, currentH, bestx, bestH, besty, temp;
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
	currentH = getH(a);
	bestH = currentH;
	bestx = posxofspace;
	besty = posyofspace;
	
	
	for (loops = 0; loops < 10000; loops++) {
		for (i = 0; i < 4; i++) {
			if (posxofspace + x[i] >=0 && posxofspace + x[i] < 3 && posyofspace + y[i] < 3 && posyofspace + y[i] >= 0) {
				temp = a[posxofspace][posyofspace];
				a[posxofspace][posyofspace] = a[posxofspace + x[i]][posyofspace + y[i]];
				a[posxofspace + x[i]][posyofspace + y[i]] = temp;
				h = getH(a);

				// 还原回来原来的状态
				temp = a[posxofspace][posyofspace];
				a[posxofspace][posyofspace] = a[posxofspace + x[i]][posyofspace + y[i]];
				a[posxofspace + x[i]][posyofspace + y[i]] = temp;

				if (h < bestH) {
					bestx = posxofspace + x[i];
					besty = posyofspace + y[i];
					bestH = h;
					break;
				}

			}
		}

		if (isReached(a))
			break;


		if (bestH == currentH) {
			for (int g = 0; g < range; g++) {
				i = rand() % 4;
				if (posxofspace + x[i] >=0 && posxofspace + x[i] < 3 && posyofspace + y[i] < 3 && posyofspace + y[i] >= 0) {
					temp = a[posxofspace][posyofspace];
					a[posxofspace][posyofspace] = a[posxofspace + x[i]][posyofspace + y[i]];
					a[posxofspace + x[i]][posyofspace + y[i]] = temp;
					h = getH(a);
					if (h > currentH) {	
						// 还原回来原来的状态
						temp = a[posxofspace][posyofspace];
						a[posxofspace][posyofspace] = a[posxofspace + x[i]][posyofspace + y[i]];
						a[posxofspace + x[i]][posyofspace + y[i]] = temp;
					} else {
						posxofspace += x[i];
						posyofspace += y[i]; 
					}
				}
			}
			if (bestH == currentH)
				return false;
		} else {
			currentH = bestH;
			temp = a[posxofspace][posyofspace];
			a[posxofspace][posyofspace] = a[bestx][besty];
			a[bestx][besty] = temp;
			posxofspace = bestx;
			posyofspace = besty;
		}
	}
	// cout << currentH << endl;
	return isReached(a);
}

int main(int argc, char const *argv[])
{
	int i, j, k, count = 0, a[3][3], test[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, test1[3][3] = {{7, 2, 4}, {5, 9, 6}, {8 ,3 ,1}};
	while(cin >> a[0][0]) {
		// getRandomStart(a);
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
	cout << "Steepest HillClimb algorithm in solving the 8-puzzle problem:\nSolved percentage: ";
	cout << ((double)count / (double)10000 * (double)100) << "%" << endl;
	return 0;
}