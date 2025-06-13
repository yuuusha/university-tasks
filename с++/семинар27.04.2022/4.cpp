#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

int main() {

	int n, num, min;
	cin >> n;

	//vector
	/*vector<int> vnum;
	for (int i = 0; i < n; i++) {
		cin >> num;
		vnum.push_back(num);
	}
	min = vnum[0];
	for (int i = 1; i < n; i++)
		if (min > vnum[i])
			min = vnum[i];
	vnum.insert(vnum.begin() + 1, min);*/
	
	//list
	/*list<int> lnum;
	for (int i = 0; i < n; i++) {
		cin >> num;
		lnum.push_back(num);
	}
	min = *(lnum.begin());
	for (auto it = ++lnum.begin(); it != lnum.end(); it++)
		if (min > *it)
			min = *it;
	lnum.insert(++lnum.begin(), min);*/

	//stack
	/*stack<int> snum;
	stack<int> ssnum;
	for (int i = 0; i < n; i++) {
		cin >> num;
		snum.push(num);
	}
	min = snum.top();
	while (!snum.empty()) {
		int t = snum.top();
		snum.pop();
		if (min > t)
			min = t;
		ssnum.push(t);
	}
	int t = ssnum.top();
	ssnum.pop();
	snum.push(t);
	snum.push(min);
	while (!ssnum.empty()) {
		t = ssnum.top();
		ssnum.pop();
		snum.push(t);
	}
	while (!snum.empty()) {
		t = snum.top();
		snum.pop();
		ssnum.push(t);
	}*/

	//queue
	/*queue<int> qnum;
	int t;
	for (int i = 0; i < n; i++) {
		cin >> num;
		qnum.push(num);
	}
	min = qnum.front();
	for (int i = 0; i < n; i++) {
		t = qnum.front();
		qnum.pop();
		if (min > t)
			min = t;
		qnum.push(t);
	}
	t = qnum.front();
	qnum.pop();
	qnum.push(t);
	qnum.push(min);
	for (int i = 0; i < n - 1; i++) {
		t = qnum.front();
		qnum.pop();
		qnum.push(t);
	}*/

}