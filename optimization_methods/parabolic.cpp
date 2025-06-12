#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return x * x * x + 4 * x * x - 4 * x + 1;
}

int main()
{
    double a = -1;
    double b = 2;
    double e = 1e-6;

    double x1 = a;
    double x2 = (a + b) / 2;
    double x3 = b;

    double f1 = f(x1);
    double f2 = f(x2);
    double f3 = f(x3);

    double a1, a2, fcur;

    double xcur = 0;
    double xprev = 2 * e;

    while (abs(xcur - xprev) > e) {

        a1 = (f2 - f1) / (x2 - x1);
        a2 = (1 / (x3 - x2)) * ((f3 - f1) / (x3 - x1) - (f2 - f1) / (x2 - x1));

        xprev = xcur;
        xcur = 0.5 * (x1 + x2 - a1 / a2);
        fcur = f(xcur);

        if (xcur < x2) {
            if (fcur > f2) {
                x1 = xcur;
                f1 = fcur;
            }
            else {
                x3 = x2;
                f3 = f2;
                x2 = xcur;
                f2 = fcur;
            }
        }
        else {
            if (fcur > f2) {
                x3 = xcur;
                f3 = fcur;
            }
            else {
                x1 = x2;
                f1 = f2;
                x2 = xcur;
                f2 = fcur;
            }
        }
    }
    cout << "x*: " << xcur << endl;
    cout << "f(x*): " << fcur << endl;

}
