// рекурсия 3 17
// Разработать рекурсивную функцию, не возвращающую значений, которая в заданной строке заменяет все слова, начинающиеся с заглавной буквы, на многоточия
#include <iostream>
#include <string>

using namespace std;

void rep(string &s, int i) {

	if (i < s.length()) {
		if (isupper(s[i]) && (s[i-1] == ' '))
			s.replace(i, s.find(' ', i)-i, "...");
		rep(s, i + 1);
	}
}


int main() {

	string s;
	getline(cin, s);
	s = ' ' + s;
	rep(s, 1);
	s = s.substr(1);
	cout << s;

}
/*

ввод
Hello world My frieNd

вывод
... world ... frieNd

*/