#include <iostream>
#include <string>
#include <tuple>

using namespace std;

struct stud {
    string lastname, firstname, patronymic;
    int birth;
    double a[6];
    stud(string lastname, string firstname, string patronymic, int birth, int a1, int a2, int a3, int a4, int a5) {
        this->lastname = lastname;
        this->firstname = firstname;
        this->patronymic = patronymic;
        this->birth = birth;
        this->a[0] = a1; this->a[1] = a2; this->a[2] = a3; this->a[3] = a4; this->a[4] = a5;
        this->a[5] = (a1 + a2 + a3 + a4 + a5) / 5.;
    }
    void print() {
        cout << lastname << ' ' << firstname << ' ' << patronymic << ' ' << birth << ' ' << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << ' ' << a[4] << endl;
    }
};

bool isLower(stud a, stud b) {
    return make_tuple(a.a[5], a.birth, a.lastname, a.firstname, a.patronymic) < make_tuple(-(b.a[5]), b.birth, b.lastname, b.firstname, b.patronymic);
}

template <typename type>
void bubble(type arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (isLower(arr[j + 1], arr[j]))
                swap(arr[j], arr[j + 1]);
}

int main() {

    stud A[3] = { {"Ivanov", "Ivan", "Ivanovich", 2003, 5, 5, 5, 5, 5},
                  {"Petrov", "Petr", "Petrovich", 2004, 5, 5, 5, 4, 4},
                  {"Alexandrov", "Alexandr", "Alexandrovich", 2002, 3, 3, 2, 2, 5} };

    bubble(A, 3);

    for (int i = 0; i < 3; i++)
        A[i].print();
}