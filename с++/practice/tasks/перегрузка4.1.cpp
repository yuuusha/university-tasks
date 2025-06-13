// перегрузки 4 1
#include <iostream>
#include <iomanip>

using namespace std;

float F(float x) {

	if (x >= 0.9)
		return 1 / (float)((0.1 + x) * (0.1 + x));
	else if (x < 0)
		return x * x + 0.2;
	else
		return 0.2 * x + 0.1;
}

void F(float x, float& y) {

	if (x >= 0.9)
		y = 1 / (float)((0.1 + x) * (0.1 + x));
	else if (x < 0)
		y = x * x + 0.2;
	else
		y = 0.2 * x + 0.1;

}

int main() {

	float a, b, h, y;
	cin >> a >> b >> h;

	cout << "	y	   x" << endl;
	for (float x = a; x <= b; x += h) {

		y = F(x);
		cout << setw(10) << y << ' ' << setw(10) << x << endl;

	};

	cout << "\n	y	   x" << endl;
	for (float x = a; x <= b; x += h) {

		F(x, y);
		cout << setw(10) << y << ' ' << setw(10) << x << endl;

	}

}
/*

ввод
-0.1 1 0.2

вывод
		y          x
	  0.21       -0.1
	  0.12        0.1
	  0.16        0.3
	   0.2        0.5
	  0.24        0.7
	  0.28        0.9

		y          x
	  0.21       -0.1
	  0.12        0.1
	  0.16        0.3
	   0.2        0.5
	  0.24        0.7
	  0.28        0.9

*/