#include <iostream>
#include "OOP.h"

int main() {

	DoubleLinkedList<int> mass;
	int n, num, k = 0;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> num;
		mass.InsertRight(mass.GetLength(), num);
	}

	for (int i = 2; i <= mass.GetLength(); i++) {
		if (mass.Get(i - 1) == mass.Get(i)) {
			mass.Remove(i - 1);
			k++;
			i--;
		}
	}

	cout << k << endl;
	mass.PrintLeftToRight();
	
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