#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

void print(vector<int> a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

int main() {
	
	vector<int> num = { 1,2,3,4,5,6 };

	//for_each выполняет какое-либо действие с каждым элементом массива по отдельности
	//изначально является немодифицирующим алгоритмом, т.е. не меняет исходный контейнер, однако он может быть изменен в соответствии с передаваемой функцией
	for_each(num.begin(), num.end(), [](int& a) { a = 2 * a; });
	print(num);

	//transform изменяет исходный контейнер
	//более того, этот алгоритм может работать с двумя контейнерами одновременно и\или помещать результат в новый контейнер
	transform(num.begin(), num.end(), num.begin(), [](int a) {return a / 2; });
	print(num);
}