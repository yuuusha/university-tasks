#include <iostream>
#include "arrays.h"

using namespace std;

template <typename type>
type min(type* mass, bool* &bmass, int n) {
	type m = mass[0];
	int ind = 0;
	for (int i = 0; i < n; i++) {
		if (mass[i] < m && bmass[i]) {
			m = mass[i];
			ind = i;
		}
	}
	bmass[ind] = false;
	return m;
}

template <typename type>
void naivesort(type mass, bool* bmass, int n) {

	for (int i = 0; i < n; i++) {
		cout << min(mass, bmass, n) << ' ';
	}
	
}

int main() {

	int n;
	cin >> n;

	int* mass = create<int>(n);
	bool* bmass = create<bool>(n);
	read(mass, n);

	naivesort(mass, bmass, n);
	
}