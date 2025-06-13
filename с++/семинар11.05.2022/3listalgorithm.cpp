#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <list>

using namespace std;

void print(list<int> a) {
	for (auto x : a)
		cout << x << ' ';
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

	int k;
	cin >> k;
	auto it = num.begin();
	for (int i = 1; i < k; i++) 
		it++;
	

	rotate(num.begin(), it, num.end());
	print(num);

}