#include <iostream>
#include <string>

using namespace std;

int currentdate;

class Software {
public:
	virtual void info() = 0;
	virtual bool canuse() = 0;
};

class FreeSoftware : public Software {
public:
	string name, proizv;
	FreeSoftware(string a, string b) : name(a), proizv(b) {}
	void info() {
		cout << "     Name: " << name << endl;
		cout << "     Manufacturer: " << proizv << endl;
	}
	bool canuse() {
		return true;
	}
};

class SharewareSoftware : public FreeSoftware {
public:
	int date, usage;
	SharewareSoftware(string a, string b, int c, int d) : FreeSoftware(a, b), date(c), usage(d) {}
	void info() {
		cout << "     Name: " << name << endl;
		cout << "     Manufacturer: " << proizv << endl;
		cout << "     Date of installation: " << date << endl;
		cout << "     Term of use: " << usage << endl;
	}
	bool canuse() {
		if (currentdate <= (date + usage))
			return true;
		else
			return false;
	}
};

class ProprietarySoftware : public SharewareSoftware {
public:
	int price;
	ProprietarySoftware(string a, string b, int c, int d, int e) : SharewareSoftware(a, b, c, d), price(e) {}
	void info() {
		cout << "     Name: " << name << endl;
		cout << "     Manufacturer: " << proizv << endl;
		cout << "     Date of installation: " << date << endl;
		cout << "     Term of use: " << usage << endl;
		cout << "     Price: " << price << endl;
	}
	bool canuse() {
		if (currentdate <= (date + usage))
			return true;
		else
			return false;
	}
};

void search(Software* Soft[6]) {

	for (int i = 0; i < 6; i++) {
		if (Soft[i]->canuse()) {
			cout << "You can use this: " << endl;
			Soft[i]->info();
			cout << endl;
		}
	}

}

int main() {

	setlocale(LC_ALL, "Russian");

	Software *Soft[6];
	Soft[0] = new FreeSoftware("Type A", "Microsoft");
	Soft[1] = new FreeSoftware("Type B", "Microsoft");
	Soft[2] = new SharewareSoftware("Videocard A", "Nvidia", 10, 20);
	Soft[3] = new SharewareSoftware("Videocard B", "Nvidia", 11, 20);
	Soft[4] = new ProprietarySoftware("Macbook A", "Apple", 5, 26, 1200);
	Soft[5] = new ProprietarySoftware("Macbook B", "Apple", 5, 10, 1000);

	cin >> currentdate;

	for (int i = 0; i < 6; i++) {
		cout << "Position " << i << ':' << endl;
		Soft[i]->info();
		cout << endl;
	}

	search(Soft);

}