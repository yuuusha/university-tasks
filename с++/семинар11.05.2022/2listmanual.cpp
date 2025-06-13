#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <list>

using namespace std;

bool* eratos(int n) {
	n++;
	bool* a = new bool(n);
	a[0] = false;
	a[1] = false;
	for (int i = 2; i < n; i++)
		a[i] = true;
	for (int i = 2; i * i < n; i++)
		for (int p = i * i; p < n; p += i)
			a[p] = false;
	return a;
}

void print(list<int> a) {
	for (auto x : a)
		cout << x << ' ';
	cout << endl;
}

void print(bool* a, int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << ' ';
	cout << endl;
}

int main() {

	srand(time(NULL));
	list<int> num;

	for (int i = 0; i < 20; i++) {
		int n = rand() % 100;
		num.push_back(n);
	}
	print(num);

	int mx = *max_element(num.begin(), num.end());
	bool* a = eratos(mx);

	auto k = num.begin();
	for (auto x = num.begin(); x != num.end(); x++) {
		if (a[*x]) {
			swap(*x, *k);
			k++;
		}
	}
	print(num);

}