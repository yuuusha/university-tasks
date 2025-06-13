#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <numeric>
#include <set>

using namespace std;

template <typename T>
void print(T a) {
	for (auto x : a)
		cout << x << ' ';
	cout << endl;
}

void trans(set<char>& a, string s) {
	for (int i = 0; i < s.size(); i++)
		a.insert(s[i]);
}

string tocaps(string s) {
	for (int i = 0; i < s.size(); i++)
		s[i] = (char)toupper(s[i]);
	return s;
}

int main() {

	string text = "blue red GREEN YelLoW PINK ";
	set<string> words;

	set<char> extra, extra1;
	vector<char> ans;

	int i = 0;
	int cur = text.find(' ', i);
	while (cur != string::npos) {

		string s = text.substr(i, cur - i);
		words.insert(s);

		i = cur + 1;
		cur = text.find(' ', i);
	}

	print(words);


	for (auto it = words.begin(); it != words.end(); it++) {
		if (*it == tocaps(*it))
			trans(extra, *it);
		else
			trans(extra1, tocaps(*it));
	}

	set_difference(extra.begin(), extra.end(), extra1.begin(), extra1.end(), back_inserter(ans));
	print(ans);
}