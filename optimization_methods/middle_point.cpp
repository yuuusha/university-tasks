#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return 2 * cos(x) - 0.5 * sin(x);
}

double df(double x) {
    return -2 * sin(x) - 0.5*cos(x);
}

void middle_point() {
    double a = 2;
    double b = 4;
    double e = 1e-6;
    double x, dx;

    do {
        x = (a + b) / 2;
        dx = df(x);

        if (dx > 0) {
            b = x;
        }
        else {
            a = x;
        }
    } while (abs(dx) > e);

    cout << "x*: " << x << endl;
    cout << "f(x*): " << f(x) << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Метод средней точки:" << endl;
    middle_point();
}
