#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <list>

using namespace std;

void print(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';
	cout << endl;
}

int main() {

	srand(time(NULL));
	vector<int> num;

	for (int i = 0; i < 20; i++) {
		int n = rand() % 100;
		num.push_back(n);
	}
	print(num);

	int k;
	cin >> k;

	auto it = num.begin();
	for (int i = 1; i < k; i++) {
		num.push_back(*it);
		it++;
	}
	num.erase(num.begin(), it);
	print(num);

}