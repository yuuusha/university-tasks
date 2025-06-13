#include <iostream>

using namespace std;

int** create(int n, int m) {
	int** mass = new int* [n];
	for (int i = 0; i < n; i++)
		mass[i] = new int[m];
	return mass;
}

void read(int** mass, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> mass[i][j];
}

double mult(int** mass, int i, int j, int n, int m) {

	if (j < m)
		return mass[i][j] * mult(mass, i, j + 1, n, m);
	else
		return 1;

}

double mult2(int** mass, int i, int j, int n, int m) {

	if (i < n)
		return mult(mass, i, 0, n, m) * mult2(mass, i + 1, 0, n, m);
	else
		return 1;

}

int main() {

	int n, m;
	cin >> n >> m;
	int** mass = create(n, m);
	read(mass, n, m);
	cout << mult2(mass, 0, 0, n, m);

}