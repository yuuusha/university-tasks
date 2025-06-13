#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

template <typename type>
void print(type a) {
	for (auto x : a) {
		cout << x << ' ';
	}
	cout << endl;
}

void unique(multiset<int> a, vector<int> &b) {
	for (auto i : a) {
		if (a.count(i) == 1)
			b.push_back(i);
	}
}

int main() {

	ifstream in("input.txt");
	string s;
	int n = 0;

	while (getline(in, s))
		n++;

	in.close();
	in.open("input.txt");

	vector<multiset<int>> numbers(n);
	vector<int> ans;
	
	for (int i = 0; i < n; i++) {
		while (in.peek() != '\n') {
			int num;
			in >> num;
			numbers[i].insert(num);
		}
		char ch;
		in.get(ch);
	}

	for (int i = 0; i < n / 2; i++) {
		numbers[i].insert(numbers[n - i - 1].begin(), numbers[n - i - 1].end());
		unique(numbers[i], ans);
		print(ans);
		ans.clear();
	}


}