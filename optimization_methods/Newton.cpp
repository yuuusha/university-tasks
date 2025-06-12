#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return 2 * cos(x) - 0.5 * sin(x);
}

double df(double x) {
    return -2 * sin(x) - 0.5*cos(x);
}

double d2f(double x) {
    return -2 * cos(x) + 0.5 * sin(x);
}

void Newton() {
    double a = 2;
    double b = 4;
    double e = 1e-6;
    double x = (a + b) / 2;
    double dx = df(x);
    double d2x;

    do {
        
        d2x = d2f(x);
        x = x - dx / d2x;
        dx = df(x);

    } while (abs(dx) > e);

    cout << "x*: " << x << endl;
    cout << "f(x*): " << f(x) << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Метод Ньютона:" << endl;
    Newton();
}
