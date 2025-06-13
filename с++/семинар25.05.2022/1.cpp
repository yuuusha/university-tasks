#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <numeric>
#include <set>
#include <unordered_set>

using namespace std;

class point {
public:
	int x, y;

	point(int x, int y) : x(x), y(y) {};

	void print() {
		cout << x << ' ' << y << endl;
	}

	friend bool operator< (const point& a, const point& b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}

};

void print(vector<point> a) {
	for (auto x : a)
		x.print();
	cout << endl;
}

void print(set<point> a) {
	for (auto x : a)
		x.print();
	cout << endl;
}

int main() {

	point a(1, 3);
	point b(1, 2);

	//чтобы положить класс в вектор, не требуется производить какие-либо особенные действия
	vector<point> vec;
	vec.push_back(a);
	vec.push_back(b);
	print(vec);

	//чтобы положить класс в set\map необходимо задать отношение линейного порядка внутри класса,
	//т.к. эти коллекции являются отсортированными, им нужно знать, как именно сравнивать два объекта класса
	set<point> s;
	s.insert(a);
	s.insert(b);
	print(s);
	
}