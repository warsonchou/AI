#include "iostream"
#include "fstream"
#include "stdlib.h"

using namespace std;
int main(int argc, char const *argv[])
{
	int u, i, j, num, a[9] = {1,2,3,4,5,6,7,8,9}, temp;
	ofstream out("tinyData");
	if (out.is_open()) {
		for (u = 0; u < 1; u++) {
			for (i = 0; i < 9; i++) {
				num = rand() % 9;
				temp = a[i];
				a[i] = a[num];
				a[num] = temp;
			}

			for (i = 0; i < 9; i++) {
				if (i != 0) {
					out << " ";
				}
				out << a[i];
			}
			out << "\n";
		}
	}
	out.close();
	return 0;
}