#include <iostream>
#include <algorithm>
using namespace std;

bool straight(double a, double b, double c) {
    double a1 = max(max(a, b), max(b, c));
    double b1 = min(min(a, b), min(b, c));
    double c1 = max(min(a, b), min(max(a, b), c));
    double eps = 1e-9;
    return ( abs((b1 * b1 + c1 * c1) - (a1 * a1)) < eps);

}

class triangle {
    double a, b, c;
public:

    static int n;

    triangle() : a(0), b(0), c(0) {};
    triangle(double a, double b, double c) { set(a, b, c); };

    bool set(double a, double b, double c) {
        if ((a > 0 && b > 0 && c > 0) && (min(min(a, b), min(b, c)) + max(min(a, b), min(max(a, b), c)) > max(max(a, b), max(b, c)))) {
            if (straight(a, b, c)) n++;
            if (straight(this->a, this->b, this->c)) n--;
            this->a = a;
            this->b = b;
            this->c = c;
            return true;
        };
        return false;
    }
    void get() {
        cout << a << ' ' << b << ' ' << c << endl;
    }

    double perimeter() {
        return (a + b + c);
    }
    double square() {
        double pp = perimeter() / 2.0;
        return sqrt(pp * (pp - a) * (pp - b) * (pp - c));
    }

    friend bool operator==(triangle& a, triangle& b) {
        return (a.a == b.a && a.b == b.b && a.c == b.c);
    }
    friend bool operator!=(triangle& a, triangle& b) {
        return !(a==b);
    }

};

int triangle::n = 0;

int main() {
    
    triangle a(3, 4, 5);
    a.set(3,4,7);
    cout << triangle::n;
    
}