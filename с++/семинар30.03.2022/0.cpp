#include <iostream>
#include <vector>

using namespace std;

struct point {
	double x, y;
	point() : x(0), y(0) {};
	point(int x, int y) : x(x), y(y) {};
};

double dist(point a, int x, int y) {
	return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
}

class rectangle {

	point o;
	int a, b;

public:

	rectangle() : o(), a(0), b(0) {};
	rectangle(int x, int y, int a, int b) { create(x, y, a, b); };

	void getO() {
		cout << "(" << o.x << ", " << o.y << ")";
	}
	void getOO() {
		cout << "(" << o.x+a << ", " << o.y+b << ")";
	}
	int getA() {
		return a;
	}
	int getB() {
		return b;
	}
	void getCenter() {
		point c = center();
		cout << "(" << c.x << ", " << c.y << ")";
	}
	void get() {
		getO();
		cout << ' ' << getA() << ' ' << getB() << ' ';
		getOO();
		cout << ' ';
		getCenter();
		cout << endl;
	}

	void create(int x, int y, int a, int b) {
		this->o.x = x;
		this->o.y = y;
		if (a >= 0 && b >= 0) {
			this->a = a;
			this->b = b;
		}
	}
	void move(int x, int y) {
		o.x += x;
		o.y += y;
	}
	void reposition(int x, int y) {
		o.x = x;
		o.y = y;
	}
	void resize(int a, int b) {
		if (a > 0 && b > 0) {
			this->a = a;
			this->b = b;
		}
	}
	point center() {
		point c;
		c.x = this->o.x + this->a / 2.0;
		c.y = this->o.y + this->b / 2.0;
		return c;
	}

};

class setRectangle {

	vector<rectangle> vect;

public: 

	void add(rectangle a) {
		vect.push_back(a);
	}

	void ktoeto(int x, int y) {

		rectangle temp;
		double min = 1000;
		for (int i = 0; i < vect.size(); i++) {
			if (dist(vect[i].center(), x, y) < min) {
				min = dist(vect[i].center(), x, y);
				temp = vect[i];
			}
		}

		temp.get();
	}

};

int main() {

	rectangle R(1, 1, 2, 3);
	rectangle T(0, 0, 2, 3);
	rectangle W(2, 1, 2, 3);

	R.get();
	T.get();
	W.get();

	setRectangle set;
	set.add(R);
	set.add(T);
	set.add(W);
	set.ktoeto(2,2.5);

}