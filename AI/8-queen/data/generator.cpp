#include "iostream"
#include "fstream"
#include "stdlib.h"

using namespace std;

struct queen{
	int x; //position
	int y;
};


bool isSafe(queen q[], int &x, int &y) {
	bool safe = true;
	int i;
	for (i = 0; i < 8; i++) {
		if (q[i].x == x && q[i].y == y) {
			safe = false;
			break;
		}
	}
	return safe;
}

int main(int argc, char const *argv[])
{
	int u, i, j, num, temp, x, y;
	queen q[8];
	q[0].x = 0;
	q[0].y = 4;

	q[1].x = 1;
	q[1].y = 5;

	q[2].x = 2;
	q[2].y = 6;

	q[3].x = 3;
	q[3].y = 3;

	q[4].x = 4;
	q[4].y = 4;

	q[5].x = 5;
	q[5].y = 5;

	q[6].x = 6;
	q[6].y = 6;

	q[7].x = 7;
	q[7].y = 7;
	ofstream out("tinytestData");
	if (out.is_open()) {
		for (u = 0; u < 50; u++) {
			for (i = 0; i < 8; i++) {
				x = rand() % 8;
				y = rand() % 8;
				if (isSafe(q, x, y)) {
					q[i].x = x;
					q[i].y = y;
				}
			}

			for (i = 0; i < 8; i++) {
				if (i != 0) {
					out << " ";
				}
				out << q[i].x << " " << q[i].y;
			}
			out << "\n";
		}
	}
	out.close();
	return 0;
}


// q[0].x = 0;
	// q[0].y = 4;

	// q[1].x = 1;
	// q[1].y = 5;

	// q[2].x = 2;
	// q[2].y = 6;

	// q[3].x = 3;
	// q[3].y = 3;

	// q[4].x = 4;
	// q[4].y = 4;

	// q[5].x = 5;
	// q[5].y = 5;

	// q[6].x = 6;
	// q[6].y = 6;

	// q[7].x = 7;
	// q[7].y = 7;
// --------------
	// q[0].x = 0;
	// q[0].y = 7;

	// q[1].x = 1;
	// q[1].y = 2;

	// q[2].x = 2;
	// q[2].y = 6;

	// q[3].x = 3;
	// q[3].y = 3;

	// q[4].x = 4;
	// q[4].y = 1;

	// q[5].x = 5;
	// q[5].y = 4;

	// q[6].x = 6;
	// q[6].y = 0;

	// q[7].x = 7;
	// q[7].y = 5;

// --------------
	// q[0].x = 0;
	// q[0].y = 3;

	// q[1].x = 1;
	// q[1].y = 1;

	// q[2].x = 2;
	// q[2].y = 7;

	// q[3].x = 3;
	// q[3].y = 4;

	// q[4].x = 4;
	// q[4].y = 6;

	// q[5].x = 5;
	// q[5].y = 0;

	// q[6].x = 6;
	// q[6].y = 2;

	// q[7].x = 7;
	// q[7].y = 5;