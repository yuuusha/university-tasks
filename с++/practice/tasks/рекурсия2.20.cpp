// рекурсия II 20
// Разработать рекурсивную функцию, возвращающую значение для вычисления суммы элементов одномерного массива
#include <iostream>

using namespace std;

int sum(int* mass, int i, int n) {

	if (i < n)
		return mass[i] + sum(mass, i + 1, n);
	else
		return 0;


}

int main() {

	int n, num;
	cin >> n;
	int* mass = new int[n];

	for (int i = 0; i < n; i++)
		cin >> mass[i];

	cout << sum(mass, 0, n);

}
/*

ввод
5
1 2 3 4 5

вывод
15

*/