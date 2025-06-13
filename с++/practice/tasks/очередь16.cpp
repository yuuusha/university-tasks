#include <iostream>
#include "OOP.h"

int main() {

	Queue<int> mass;
	int n, num, k = 0, el, el1, ncopy;
	cin >> n;
	ncopy = n;

	for (int i = 0; i < n; i++) {
		cin >> num;
		mass.Put(num);
	}

	el = mass.Get();
	mass.Put(el);
	for (int i = 0; i < n - 1; i++) {
		el1 = mass.Get();
		if (el != el1) {
			mass.Put(el1);
		}
		else {
			k++;
			ncopy--;
		}
		el = el1;
	}

	cout << k << endl;
	for (int i = 0; i < ncopy; i++) {
		cout << mass.Get() << ' ';
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