#include <iostream>
using namespace std;

double f(double x) {
    return 2 * x * x - 8 * x - 7;
}

int main()
{
    double a = 0;
    double b = 3;
    double h = 0.1;
    double e = 1e-6;

    double x0 = a;
    double f0 = f(x0);
    double x1, f1;

    while (abs(h) > e) {
        x1 = x0 + h;
        f1 = f(x1);

        if (f0 >= f1) {
            x0 = x1;
            f0 = f1;
            if (!((x0 > a) && (x0 < b))) {
                break;
            }
        }
        else {
            x0 = x1;
            f0 = f1;
            h = -h / 4;
        }
    }

    cout << "x*: " << x0 << endl;
    cout << "f(x*): " << f0 << endl;
}
