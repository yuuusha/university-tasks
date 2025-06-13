#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct student {
	string firstname, lastname, patronymic;
	int year;
	int marks[5];
};

bool compname(student a, student b) {
	return (a.firstname < b.firstname);
}

bool compyear(student a, student b) {
	return (a.year < b.year);
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int n, i = 0;
	vector <student> mass(4);

	in >> n;

	while (!in.eof()) {
		in >> mass[i].firstname >> mass[i].lastname >> mass[i].patronymic >> mass[i].year;
		for (int j = 0; j < 5; j++)
			in >> mass[i].marks[j];
		i++;
	}

	sort(mass.begin(), mass.end(), compname);

	out << n << endl;
	for (int j = 0; j < i; j++) {
		out << mass[j].firstname << ' ' << mass[j].lastname << ' ' << mass[j].patronymic << ' ' << mass[j].year << ' ';
		for (int z = 0; z < 5; z++)
			out << mass[j].marks[z] << ' ';
		out << endl;
	}

	stable_sort(mass.begin(), mass.end(), compyear);

	out << endl;
	for (int j = 0; j < i; j++) {
		out << mass[j].firstname << ' ' << mass[j].lastname << ' ' << mass[j].patronymic << ' ' << mass[j].year << ' ';
		for (int z = 0; z < 5; z++)
			out << mass[j].marks[z] << ' ';
		out << endl;
	}

}

/*
ввод

141
Диев Илья Николаевич 2003 5 5 5 5 5
Павел Еникеев Батькович 2002 5 5 5 5 5
Петр Иванов Александрович 2000 4 4 4 4 4
Иван Петров Алексеевич 2000 3 3 5 5 4

вывод

141
Диев Илья Николаевич 2003 5 5 5 5 5 
Иван Петров Алексеевич 2000 3 3 5 5 4 
Павел Еникеев Батькович 2002 5 5 5 5 5 
Петр Иванов Александрович 2000 4 4 4 4 4 

Иван Петров Алексеевич 2000 3 3 5 5 4 
Петр Иванов Александрович 2000 4 4 4 4 4 
Павел Еникеев Батькович 2002 5 5 5 5 5 
Диев Илья Николаевич 2003 5 5 5 5 5 


*/