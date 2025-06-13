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

	int num;
	set<int> a;
	set<int> even = { 0,2,4,6,8 };
	set<int> odd = { 1,3,5,7,9 };
	set<int> numbers = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> ans, ans1;
	cin >> num;
	
	//a
	while (num > 0) {
		a.insert(num % 10);
		num /= 10;
	}
	print(a);

	//б
	set_difference(a.begin(), a.end(), odd.begin(), odd.end(), back_inserter(ans));
	print(ans);
	ans.clear();

	//в
	set_difference(a.begin(), a.end(), even.begin(), even.end(), back_inserter(ans));
	print(ans);
	ans.clear();

	//г
	set_difference(numbers.begin(), numbers.end(), a.begin(), a.end(), back_inserter(ans));
	print(ans);
	
	//д
	set_difference(ans.begin(), ans.end(), even.begin(), even.end(), back_inserter(ans1));
	print(ans1);

}