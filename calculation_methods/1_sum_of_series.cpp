#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double e = 1e-3;

	cout << "    x  |      Sn      |      n  " << endl;
	cout << "-------------------------------" << endl;

	for (int x = -20; x <= 20; x += 1) {

		double y = x;
		double Sn = 0;
		int i = 2;
		int n = 0;

		while (abs(y) > e) {

			n++;
			Sn += y;
			y = y * ((-1) * x * x) / ((i) * (i + 1));

			i += 2;

		}

		cout << setprecision(6) << setw(6) << x << " | " << setw(12) << Sn << " | " << setw(6) << n + 1 << endl;

	}

}
