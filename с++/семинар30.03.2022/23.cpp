#include <iostream>
#include <string>
#include "arrays.h"

using namespace std;

void sort(string* &mass, int n) {

	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (mass[j-1].size() > mass[j].size())
			swap(mass[j - 1], mass[j]);
		}
	}
	
}

void lecsort(string*& mass, int n) {

	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (mass[j - 1].size() > mass[j].size() || (mass[j - 1].size() == mass[j].size() && mass[j - 1] > mass[j]))
				swap(mass[j - 1], mass[j]);
		}
	}

}

int main() {

	int n;
	cin >> n;
	string* mass = create<string>(n);
	read(mass, n);
	lecsort(mass, n);
	print(mass, n);

}