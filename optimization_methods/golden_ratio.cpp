#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return 2 * x * x - 8 * x - 7;
}

int main()
{
    double a = 0;
    double b = 3;
    double e = 1e-6;
    double en = (b - a) / 2;
    
    double const T = (sqrt(5) - 1) / 2;
    double const T1 = (3 - sqrt(5)) / 2;

    double x1 = a + (b - a) * T1;
    double x2 = a + (b - a) * T;
    double f1 = f(x1);
    double f2 = f(x2);

    while (en > e) {
        if (f1 <= f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - (b - a) * T;
            f1 = f(x1);
        }
        else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = b - (b - a) * T1;
            f2 = f(x2);
        }
        en = T * en;
    }

    cout << "x*: " << (a + b) / 2 << endl;
    cout << "f(x*): " << f((a + b) / 2) << endl;
    
}
