#include <iostream>
#include <iomanip>
using namespace std;

double Ln(double x, int n, double (*f)[2]) {

    double l = 0;
    double fraqU;
    double fraqD;

    for (int i = 0; i < n; i++) {
        
        fraqU = 1;
        fraqD = 1;

        for (int j = 0; j < n; j++) {
            if (j != i) {
                fraqU *= (x - f[j][0]);
            }
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                fraqD *= (f[i][0] - f[j][0]);
            }
        }

        l += f[i][1] * (fraqU / fraqD);
    }

    return l;
}

int main()
{
    int n = 4;
    double f[4][2] = { {-2,-8}, {-1, -1}, {0, 0}, {2, 8} };
    double x;

    cout << "   x   |   f" << endl;
    cout << "---------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(6) << f[i][0] << " | " << setw(6) << f[i][1] << endl;
    }

    cout << endl;
    cout << "   x   |   f" << endl;
    cout << "---------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(6) << f[i][0] << " | " << setw(6) << f[i][1] << endl;

        if (i != n - 1) {
            x = (f[i][0] + f[i + 1][0]) / 2;
            cout << setw(6) << x << " | " << setw(6) << Ln(x, n, f) << endl;
        }

    }
}
