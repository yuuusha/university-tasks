#include <iostream>
#include <iomanip>
using namespace std;

double* RR(int n, double(*f)[2]) {

    double* res = new double[n * (n - 1) / 2];
    int n_ = n;

    for (int i = 0; i < n; i++) {
        res[i] = f[i][1];
    }

    int k = 1, l = n - k;
    while (n_ < n*(n+1)/2) {

        for (int i = n_, j = 0; i < n_ + (n_ - 1); i++, j++) {
            res[i] = (res[i - l] - res[i - l - 1]) / (f[j+k][0] - f[j][0]);
        }
        k++;
        n_ = n_ + l;
        l = (n - k);

    }

    return res;
}

double Nn(double x, int n, double* rr, double(*f)[2]) {

    double pn = rr[0];
    double sk_x = 1;

    int n_ = n;
    for (int i = 0; i < n - 1;) {


        sk_x *= (x - f[i][0]);
        pn += rr[n_]*sk_x;
        
        i++;
        n_ = n_ + (n - i);
    }

    return pn;
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


    double* rr = RR(n, f);

    cout << endl;
    cout << "   x   |   f" << endl;
    cout << "---------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(6) << f[i][0] << " | " << setw(6) << f[i][1] << endl;

        if (i != n - 1) {
            x = (f[i][0] + f[i + 1][0]) / 2;
            cout << setw(6) << x << " | " << setw(6) << Nn(x, n, rr, f) << endl;
        }

    }
}
