// шаблоны 5 16
// Если количество строк в массиве нечетное - поменять местами по правилу: 1-ю строку со 2-й, 3-ю с 4-й и так далее. 
#include <iostream>

using namespace std;

double** create(int n, int m) {
	double** mass = new double* [n];
	for (int i = 0; i < n; i++)
		mass[i] = new double[m];
	return mass;
}

template <typename N>
void read(N** mass, int n, int m) {

	N t;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> t;
			mass[i][j] = t;
		}
}

template <typename N>
void print(N** mass, int n, int m) {
	for (int i = 0; i < n; i++, cout << endl)
		for (int j = 0; j < m; j++)
			cout << mass[i][j] << '\t';
}

template <typename N>
void transpose(N** mass, int n) {

	for (int i = 0; i < n; i +=2) {
		swap(mass[i], mass[i + 1]);
	}

}

int main() {

	int n, m;
	cin >> n >> m;

	double** mass = create(n, m);

	read(mass, n, m);
	cout << endl;
	print(mass, n, m);

	if (n % 2 == 0)
		transpose(mass, n);

	cout << endl;
	print(mass, n, m);

}
/*

ввод
4 4
1 2 3 4
2 3 4 5
3 4 5 6
4 5 6 7

вывод
2       3       4       5
1       2       3       4
4       5       6       7
3       4       5       6

*/