#include <iostream>
#include "OOP.h"

int main() {

	List<int> mass;
	int n, num;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> num;
		mass.Insert(mass.GetLength() + 1, num);
	}

	cout << mass.DeleteDuplicate() << endl;

	mass.Print();
	
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