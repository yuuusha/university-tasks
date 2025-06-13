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
	vector <candy> bag1(5);
	vector<candy>::iterator it;

	while (!in.eof()) {
		in >> bag1[i].name >> bag1[i].type >> bag1[i].comp >> bag1[i].mass >> bag1[i].count;
		i++;
	}

	for (int i = 0; i < 5; i++) {
		cout << bag1[i].name << ' ' << bag1[i].type << ' ' << bag1[i].comp << ' ' << bag1[i].mass << ' ' << bag1[i].count;
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 3; i++) {
		bag1.erase(bag1.begin());
		candy temp;
		cin >> temp.name >> temp.type >> temp.comp >> temp.mass >> temp.count;
		bag1.push_back(temp);
	}

	it = --bag1.end();
	cin >> n;
	(*it).count = n;

	cout << endl;
	for (int i = 0; i < bag1.size(); i++) {
		cout << bag1[i].name << ' ' << bag1[i].type << ' ' << bag1[i].comp << ' ' << bag1[i].mass << ' ' << bag1[i].count;
		cout << endl;
	}

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
10

вывод

Alenka chocolate nuts 50 1
Milka chocolate strawberry 60 1
Marshmallow marmalade apple 55 5
M&Ms chocolate nuts 50 2
Licorice lollipop mint 45 10

*/