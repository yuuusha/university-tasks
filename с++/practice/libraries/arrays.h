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

void print(int** mass, int n, int m) {
	for (int i = 0; i < n; i++, cout << endl)
		for (int j = 0; j < m; j++)
			cout << mass[i][j] << '\t';
}

void deleted(int** mass, int n, int m) {
	for (int i = 0; i < n; i++)
		delete[] mass[i];
	delete[] mass;
	mass = nullptr;
}



int* create(int n) {
	int* mass = new int [n];
	return mass;
}

void read(int* mass, int n) {
	for (int i = 0; i < n; i++)
		cin >> mass[i];
}

void print(int* mass, int n) {
	for (int i = 0; i < n; i++)
			cout << mass[i] << '\t';
}

void deleted(int* mass, int n) {
	delete[] mass;
	mass = nullptr;
}