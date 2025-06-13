#include <iostream>
#include <string>

using namespace std;

class SimpleVector {
public:
    
    int cur;
    int size;
    int* a;
    bool* ba;

    SimpleVector() {
        this->size = 1;
        this->a = new int[size];
        this->ba = new bool[size];
        ba[0] = 0;
        this->cur = 0;
    }

    SimpleVector(int size) {
        this->size = size;
        this->a = new int[size];
        this->ba = new bool[size];
        for (int i = 0; i < size; i++)
            ba[i] = 0;
        this->cur = 0;
    }

    ~SimpleVector() {
        delete[] a;
        delete[] ba;
    }

    void print() {
        for (int i = 0; i < size; i++)
            if (ba[i])
                cout << a[i] << ' ';
        cout << endl;
    }

    void printB() {
        for (int i = 0; i < size; i++)
            cout << ba[i] << ' ';
        cout << endl;
    }

    int operator[] (int n) {
        return a[n];
    }

    int& at(int n) {
        ba[n] = 1;
        return a[n];
    }

    int push_back(int num) {

        while (ba[cur])
            cur++;

        if (cur >= size) {
            size = size * 2;
            {
                int* b = new int[size];
                bool* bba = new bool[size];
                for (int i = 0; i < size / 2 + 1; i++) {
                    b[i] = a[i];
                    bba[i] = ba[i];
                }
                delete[] a;
                delete[] ba;
                this->a = b;
                this->ba = bba;
            }
        }

        a[cur] = num;
        ba[cur] = 1;

        return cur;
    }

    int find(int num) {
        for (int i = 0; i < size; i++) {
            if (ba[i] == 1 && a[i] == num)
                return i;
        }
        return -1;
    }

    void remove(int num) {
        int i = find(num);
        if (i == -1) return;
        a[i] = 0;
        ba[i] = 0;
        cur = min(cur,i);
    }

    bool insert_after(int wh, int num) {
        int i = find(wh);
        if (i == -1) return false;
        int j = push_back(num);
        while (i + 1 < j) {
            swap(a[i + 1], a[j]);
            i++;
        }
        return true;
    }
};

int main() {

    SimpleVector vass(6);
    vass.push_back(3);
    vass.push_back(4);
    vass.push_back(5);
    vass.push_back(6);

    vass.print();

    vass.insert_after(3, 2);

    vass.print();


}