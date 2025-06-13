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

int main() {

	string word;
	set<char> a;
	set<char> vowel = { 'a', 'e', 'i', 'o', 'u', 'y' };
	set<char> consonant = { 'z', 'x', 'w', 'v', 't', 's', 'r', 'q', 'p', 'n', 'm', 'l', 'k', 'j', 'h', 'g', 'f', 'd', 'c', 'b' };
	set<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	vector<char> ans, ans1;
	cin >> word;

	//a
	for (int i = 0; i < word.size(); i++)
		a.insert(word[i]);
	print(a);

	//б
	set_difference(a.begin(), a.end(), consonant.begin(), consonant.end(), back_inserter(ans));
	print(ans);
	ans.clear();

	//в
	set_difference(a.begin(), a.end(), vowel.begin(), vowel.end(), back_inserter(ans));
	print(ans);
	ans.clear();

	//г
	set_difference(letters.begin(), letters.end(), a.begin(), a.end(), back_inserter(ans));
	print(ans);

	//д
	set_difference(ans.begin(), ans.end(), vowel.begin(), vowel.end(), back_inserter(ans1));
	print(ans1);

}