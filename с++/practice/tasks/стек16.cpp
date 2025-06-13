#include <iostream>
#include "OOP.h"

int main() {

	Stack mass, mass1;
	int n, num, ncopy, k = 0;
	cin >> n;
	ncopy = n;

	for (int i = 0; i < n; i++) {
		cin >> num;
		mass.Push(num);
	}

	mass1.Push(mass.Pop());

	for (int i = 0; i < n - 1; i++) {
		if (mass1.Top() != mass.Top()) {
			mass1.Push(mass.Pop());
		}
		else {
			mass.Pop();
			ncopy--;
			k++;
		}
	}

	cout << k << endl;
	for (int i = 0; i < ncopy; i++) {
		cout << mass1.Pop() << ' ';
	}

}

/*
ввод
6
1 1 2 2 3 3
вывод
3
1 2 3

ввод
6
1 1 1 1 1 1
вывод
5
1
*/