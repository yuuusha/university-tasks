#include <iostream>
#include "SortedVector.h"
#include <set>
#include <chrono>
#include <random>
#include <iomanip>

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main()
{

    random_device rd;
    mt19937 gen(rd());

    vector<Student> tmp;
    SortedVector<Student> MyVec;
    set<Student> MySet;
    int n = 10000;


    for (int i = 0; i < n; i++) {
        Student tmps = Student(gen_random(7), gen() % 25, gen() % 10000);
        //tmp.push_back(gen_random(20));
       tmp.push_back(tmps);
    }

    for (int i = 0; i < n; i++) {
        MyVec.Add(tmp[i]);
        //MySet.insert(tmp[i]);
    }

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < n; i++) {
        MyVec[i];
    }

    /*for (auto it = MySet.begin(); it != MySet.end(); it++) {
        (*it);
    }*/

    auto end = std::chrono::steady_clock::now();

    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(7) << elapsed.count() << endl;

}
