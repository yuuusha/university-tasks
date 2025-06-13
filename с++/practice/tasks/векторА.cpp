#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

class candy {

public:
	string name, type, comp;
	int mass, count;

};

int main() {

	ifstream in("input1.txt");

	int n, i = 0;
	list <candy> bag2;
	list<candy>::iterator it;

	while (!in.eof()) {
		candy temp;
		in >> temp.name >> temp.type >> temp.comp >> temp.mass >> temp.count;
		bag2.push_back(temp);
		i++;
	}

	for (it = bag2.begin(); it != bag2.end(); it++) {
		cout << (*it).name << ' ' << (*it).type << ' ' << (*it).comp << ' ' << (*it).mass << ' ' << (*it).count;
		cout << endl;
	}
	cout << endl;


	it = bag2.begin();
	for (int i = 0; i < 3; i++) {
		cin >> (*it).name >> (*it).type >> (*it).comp >> (*it).mass >> (*it).count;
		it++;
	}

	for (it = bag2.begin(); it != bag2.end(); it++) {
		if ((*it).type == "chocolate")
			(*it).count *= 2;
	}

	cout << endl;
	for (it = bag2.begin(); it != bag2.end(); it++) {
		cout << (*it).name << ' ' << (*it).type << ' ' << (*it).comp << ' ' << (*it).mass << ' ' << (*it).count;
		cout << endl;
	}
	cout << endl;

}

/*

ввод

Fruitella marmalade strawberry 65 4
Montpensier lollipop mint 45 5
Haribo marmalade apple 55 5
Alenka chocolate nuts 50 1
Milka chocolate strawberry 60 1

Marshmallow marmalade apple 55 5
M&Ms chocolate nuts 50 2
Licorice lollipop mint 45 5

вывод

Marshmallow marmalade apple 55 5
M&Ms chocolate nuts 50 4
Licorice lollipop mint 45 5
Alenka chocolate nuts 50 2
Milka chocolate strawberry 60 2

*/