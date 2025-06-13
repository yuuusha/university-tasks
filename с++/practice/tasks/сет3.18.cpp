#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template <typename type>
void print(type a) {
	for (auto x : a)
		cout << x << ' ';
	cout << endl;
}

int main() {

	string text = "one two three four. four five six! seven eight nine? ten eleven twelve. twenty? hundred!";
	string punc = " .?!";

	vector<string> words;
	vector<string> ans;
	vector<string> lastquest;

	set<string> narrat;
	multiset<string> other;

	int i = 0;
	int cur = text.find_first_of(punc, i);
	while (cur != string::npos) {

		string s = text.substr(i, cur-i);

		if (!s.empty()) words.push_back(s);

		if (text[cur] == '.') {
			narrat.insert(words.begin(), words.end());
			words.clear();
		}

		if (text[cur] == '!') {
			other.insert(words.begin(), words.end());
			words.clear();
		}

		if (text[cur] == '?') {
			lastquest.clear();
			lastquest = words;
			other.insert(words.begin(), words.end());
			words.clear();
		}

		i = cur+1;
		cur = text.find_first_of(punc, i);
	}

	narrat.insert(lastquest.begin(), lastquest.end());
	set_difference(other.begin(), other.end(), lastquest.begin(), lastquest.end(), back_inserter(words));
	set_difference(narrat.begin(), narrat.end(), words.begin(), words.end(), back_inserter(ans));

	print(ans);
}