#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <numeric>

using namespace std;

void print(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';
	cout << endl;
}

vector<int>::iterator iter(vector<int>& a, int i) {
	auto it = a.begin();
	for (int z = 0; z < i; z++, it++);
	return it;
}

int main() {

	srand(time(NULL));
	vector<int> num;
	
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int n = rand() % 100;
		num.push_back(n);
	}
	print(num);

	for (int z = 0; z < m; z++) {
		int i, j;
		cin >> i >> j;
		auto it = iter(num, i);
		auto it1 = iter(num, j);
		cout << accumulate(it, ++it1, 0) << endl;
	}

}