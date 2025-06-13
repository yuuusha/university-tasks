#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

void print(stack<char> a) {
	while (!a.empty()) {
		cout << a.top() << ' ';
		a.pop();
	}
	cout << endl;
}

int main() {
	
	string s;
	int n;

	stack<char> train;

	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		train.push(s[i]);
	}

	stack<char> one;
	stack<char> two;

	cin >> n;
	for (int i = 0; i < n; i++) {

		int k = 0;
		char dead, van, cur;
		cin >> s;
		dead = s[1]; van = s[0];

		while (train.top() != van) {
			switch (dead) {
			case '1': two.push(train.top()); break;
			case '2': one.push(train.top()); break;
			}
			train.pop();
			k++;
		}
		if (train.top() == van) {
			switch (dead) {
			case '1': {
				one.push(train.top());
				train.pop();
				for (int j = 0; j < k; j++) {
					train.push(two.top());
					two.pop();
				}
				break;
			}
			case '2': {
				two.push(train.top());
				train.pop();
				for (int j = 0; j < k; j++) {
					train.push(one.top());
					one.pop();
				}
				break;
			}
			}
		}
		
	}

	cout << "train: ";
	print(train);
	cout << "one: ";
	print(one);
	cout << "two: ";
	print(two);
}