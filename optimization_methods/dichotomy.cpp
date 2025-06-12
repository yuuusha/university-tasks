#include <iostream>
using namespace std;

double f(double x) {
    return 2 * x * x - 8 * x - 7;
}

int main()
{
    double a = 0;
    double b = 3;
    double e = 1e-6;
    double s = e;
    double en = 2*e;

    double x1, x2, f1, f2;

    while (en > e) {

        x1 = (a + b - s) / 2;
        x2 = (a + b + s) / 2;
        f1 = f(x1);
        f2 = f(x2);

        if (f1 <= f2) {
            b = x2;
        }
        else {
            a = x1;
        }

        en = (b - a) / 2;
    }

    cout << "x*: " << (a + b) / 2 << endl;
    cout << "f(x*): " << f((a + b) / 2) << endl;
}
