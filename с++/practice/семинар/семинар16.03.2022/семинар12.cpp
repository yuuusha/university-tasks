#include <iostream>
using namespace std;

class BBall
{
    int w;
    string color;
public:

    BBall()  // = default
    {
        w = 1;
        color = "white";
    }

    //BBall(int w, string color) : w(w), color(color) {}
    BBall(int w, string color)
    {
        setW(w);
        setColor(color);
    }

    // BBall(const BBall & other) = delete;
    BBall(const BBall& other)
    {
        w = other.w;
        color = other.color;

    }


    bool setW(int w)
    {
        if (w > 0)
        {
            this->w = w;  // (*this).w = w;
            return true;
        }
        return false;
    }

    bool setColor(string color)
    {
        if (color != "")
        {
            this->color = color;
            return true;
        }
        return false;
    }

    int getW()
    {
        return w;
    }

    string getColor()
    {
        return color;
    }

    ~BBall()
    {
        cout << "Deleted ball " << this->color << endl;
    }


    BBall& operator++()
    {
        w++;
        return *this;
    }

    BBall operator++(int)
    {
        BBall tmp = *this;
        w++;
        return tmp;
    }

    friend BBall operator+(BBall& ball, int x)
    {
        return BBall(ball.w + x, ball.color);
    }
    friend BBall operator+(int x, BBall& ball)
    {
        return ball + x;
    }
    friend bool operator<(BBall& ball1, BBall& ball2) {
        return (ball1.w < ball2.w);
    }
    friend bool operator==(BBall& ball1, BBall& ball2) {
        return (ball1.w == ball2.w && ball1.color == ball2.color);
    }
    BBall operator=(BBall& ball1) {
        w = ball1.w;
        color = ball1.color;
        return *this;
    }
};

int main() {

    BBall a(1, "white");
    BBall b(2, "white");
    a = b;
    cout << a.getW();

}