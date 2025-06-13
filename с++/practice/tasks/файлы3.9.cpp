// файлы III 9
// Создать файл, состоящий из n целых чисел. Вывести на экран все числа данного файла, не кратные заданному числу.
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ofstream out("input.dat", ios::binary);

	int n, num, k;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		out.write((char*)&num, sizeof(int));
	}
	
	out.close();

	ifstream in("input.dat", ios::binary);

	cin >> k;

	while (in.read((char*)&num, sizeof(int))) {
		if (num % k != 0)
			cout << num << ' ';
	}

	in.close();

}

/*

ввод
5
3 8 5 12 7
2

вывод
3 5 7

*/