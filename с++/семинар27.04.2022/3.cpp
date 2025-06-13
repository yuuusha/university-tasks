#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main() {

	queue<int> qnum;
	stack<int> snum;

	int n, num, t;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		qnum.push(num);
	}
	while (!qnum.empty()) {
		t = qnum.front();
		qnum.pop();
		if (t%2==0) cout << t << ' ';
		else snum.push(t);
	}
	while (!snum.empty()) {
		cout << snum.top() << ' ';
		snum.pop();
	}

}