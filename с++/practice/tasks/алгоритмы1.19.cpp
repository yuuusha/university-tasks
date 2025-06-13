#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int A = 4;

struct pole {
	string str[11] = { ".....|.....",
					   ".....|.....",
					   ".....|.....",
					   ".....|.....",
					   ".....|.....",
					   "-----------",
					   ".....|.....",
					   ".....|.....",
					   ".....|.....",
					   ".....|.....",
					   ".....|....." };
	void print() {
		for (int i = 10; i >= 0; i--) {
			cout << str[i] << endl;
		}
	}
	void set(pair<int, int> a, char ch) {
		str[a.second + 5][a.first + 5] = ch;
	}
	void set_square(int a) {
		set({ a/2,a/2 }, '+');
		set({ a/2,-a/2 }, '+');
		set({ -a/2,a/2 }, '+');
		set({ -a/2,-a/2 }, '+');
	}

} pole;

void show(vector < pair<int, int>> a) {
	for (auto it = a.begin(); it != a.end(); it++, cout << endl)
		cout << (*it).first << ' ' << (*it).second;
}

double dist(pair<int, int> a) {
	return sqrt(a.first * a.first + a.second * a.second);
}

bool comp(pair<int, int> a, pair<int, int> b) {
	return (dist(a) > dist(b));
}

bool comp1(pair<int, int> a, pair<int, int> b) {
	return (dist(a) < dist(b));
}

int main() {

	vector<pair<int, int>> point;
	point.push_back({ 1, 1 });
	point.push_back({ 3, 2 });
	point.push_back({ 1, 2 });
	point.push_back({ 3, 4 });
	point.push_back({ -1, -2 });
	point.push_back({ -3, -4 });
	point.push_back({ 4, 5 });

	{
		pole.set({ 1,1 }, 'A');
		pole.set({ 3,2 }, 'B');
		pole.set({ 1,2 }, 'C');
		pole.set({ 3,4 }, 'D');
		pole.set({ -1,-2 }, 'E');
		pole.set({ -3,-4 }, 'F');
		pole.set({ 4,5 }, 'G');
		pole.set_square(A);
	}

	cout << "Before: " << endl;
	show(point);

	//а
	auto it = remove_if(point.begin(), point.end(), [](const pair<int, int>& a) {
		return (abs(a.second) <= A / 2 && abs(a.first) <= A / 2);
		});
	point.erase(it, point.end());
	cout << "Points not inside a square with side " << A << ":" << endl;
	show(point);

	//б
	auto count = count_if(point.begin(), point.end(), [](const pair<int, int>& a) {
		return (a.first < 0);
		});
	cout << "Number of points to the right of the oy-axis: " << count << endl;

	//в
	sort(point.begin(), point.end(), comp1);
	auto it2 = find_if(point.begin(), point.end(), [](const pair<int, int>& a) {
		return (a.second > abs(a.first));
		});
	cout << "The closer to the axis point above y=|x|: " << (*it2).first << ' ' << (*it2).second << endl;

	//г
	stable_sort(point.begin(), point.end(), comp);
	cout << "Sort in order of approximation to the axis: " << endl;
	show(point);

	cout << endl;
	pole.print();

}