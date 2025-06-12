#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x) {
    return (x + 4) * (x + 1) * x * (x - 2) + 30;
}

void polylines() {
    double a = -4;
    double b = 2;
    double L = 72;
    double e = 1e-6;

    double x0 = 0.5 * (f(a) - f(b) + L * (a + b)) / L;
    double f0 = f(x0);
    double p = 0.5 * (f(a) + f(b) + L * (a - b));
    double delta = 0.5 * (f0 - p) / L;
    double x1, x2;

    while (2 * L * delta > e) {

        x1 = x0 - delta;
        x2 = x0 + delta;

        if (f(x1) < f(x2)) {
            x0 = x1;
        }
        else {
            x0 = x2;
        }
        f0 = f(x0);

        p = 0.5 * (f0 + p);
        delta = 0.5 * (f0 - p) / L;
    }

    cout << setprecision(12) << "x*: " << x0 << endl;
    cout << "f(x*): " << setprecision(12) << f0 << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Метод ломаных: " << endl;
    polylines();
}
