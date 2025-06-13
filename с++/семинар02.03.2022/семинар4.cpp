#include <iostream>

using namespace std;

template <typename type>
type** create(int n, int m) {
	type** mass = new type * [n];
	for (int i = 0; i < n; i++)
		mass[i] = new type[m];
	return mass;
}

int main() {

	int n, m;
	cin >> n >> m;
	int** mass = create<int>(n, m);

}