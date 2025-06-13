#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

int currentyear = 2022;

int count(string a) {
	int k = 0;
	for (int i = 0; i < a.size(); i++)
		if (a[i] == ' ')
			k++;
	return k;
}

class singer {

	friend bool operator< (const singer& a, const singer& b) {
			return (a.name < b.name);
	}

public:
	string name, info, country, beginyear;
	singer() : name(" "), info(" "), country(" "), beginyear(" ") {};

	void change(string newname) {
		name = newname;
	}

	void changeinfo(string newinfo) {
		info = newinfo;
	}

	void changeyear(string year) {
		beginyear = year;
	}

	void changecountry(string newcountry) {
		country = newcountry;
	}

};

class song {

	friend bool operator< (const song& a, const song& b) {
		return (a.name < b.name);
	}

public:
	string name, genre, year;
	song() : name(" "), year(" "), genre(" ") {};
};

class Player {
public:
	map<singer, vector<song>> player;

	map<singer, vector<song>>::iterator find(string name) {
		for (auto it = player.begin(); it != player.end(); it++) {
			if ((*it).first.name == name)
				return it;
		}
		return player.end();
	}

	void add(string artname, song b) {
		auto it = find(artname);
		if (it == player.end()) { cout << "none"; return; };
		player[it->first].push_back(b);
	}

	void add(singer a, song b) {
		player[a].push_back(b);
	}

	void add(singer a) {
		player[a];
	}

	void erase(singer a) {
		player.erase(player.find(a));
	}

	void erase_song(string artistname, string songname) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return; };
		for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++)
			if ((*it1).name == songname) {
				(*it).second.erase(it1);
				return;
			}
		cout << "none" << endl;
	}

	void change_name(string oldname, string newname) {
		auto it = find(oldname);
		if (it == player.end()) { cout << "none"; return; };
		singer temp = it->first;
		temp.change(newname);
		player[temp] = it->second;
		player.erase(it);
	}

	void change_info(string artistname, string info) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return; };
		singer temp = it->first;
		vector<song> stemp = it->second;
		player.erase(it);
		temp.changeinfo(info);
		player[temp] = stemp;
	}

	void change_country(string artistname, string country) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return; };
		singer temp = it->first;
		vector<song> stemp = it->second;
		player.erase(it);
		temp.changecountry(country);
		player[temp] = stemp;
	}

	void change_year (string artistname, string year) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return; };
		singer temp = it->first;
		vector<song> stemp = it->second;
		player.erase(it);
		temp.changeyear(year);
		player[temp] = stemp;
	}

	void change_song(string artistname, string oldsongname, string newname) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return; };
		for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++)
			if ((*it1).name == oldsongname) {
				(*it1).name = newname;
				return;
			}
		cout << "none" << endl;
	}

	void search_song_by_year(string year1, string year2) {
		for (auto i : player) {
			if (minyear(i.first.name) < year2 && minyear(i.first.name) > year1)
				cout << i.first.name << endl;
		}
	}

	string maxyear(string artistname) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return " "; };
		string max;
		for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++) {
			if (max < (*it1).year)
				max = (*it1).year;
		}
		return max;
	}

	string minyear(string artistname) {
		auto it = find(artistname);
		if (it == player.end()) { cout << "none"; return " "; };
		string min = "2999";
		for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++) {
			if (min > (*it1).year)
				min = (*it1).year;
		}
		return min;
	}

	void delete_if_no_genre(string genre) {
		for (auto i = player.begin(); i != player.end();) {
			int k = 0;
			for (auto it = (*i).second.begin(); it != (*i).second.end(); it++) {
				if ((*it).genre == genre) {
					k++;
					break;
				}
			}
			if (k == 0) {
				i = player.erase(i);
				continue;
			}
			i++;
		}
	}

	void delete_if_no_songs(int n) {
		for (auto i = player.begin(); i != player.end();) {
			if (maxyear((*i).first.name) < to_string(currentyear-n)) {
				i = player.erase(i);
				continue;
			}
			i++;
		}
	}

	void if_break(string groupname, string oneartist) {
		auto it = find(groupname);
		if (it == player.end()) { cout << "none"; return; };
		singer newsinger;
		newsinger = (*it).first;
		newsinger.name = oneartist;
		string nyear = maxyear((*it).first.name);
		vector<song> temp;
		for (auto i = (*it).second.begin(); i != (*it).second.end();) {
			if ((*i).year == nyear) {
				temp.push_back(*i);
				i = (*it).second.erase(i);
				continue;
			}
			i++;
		}
		player[newsinger] = temp;
	}

	void show_one_word() {
		for (auto i : player) {
			for (auto it = i.second.begin(); it != i.second.end(); it++) {
				if (count((*it).name) == 0)
					cout << i.first.name << ' ' << i.first.info << ' ' << i.first.beginyear << ' ' << i.first.country << ": " << (*it).name << ' ' << (*it).year << ' ' << (*it).genre << endl;
			}		
		}
	}

	void show(string name) {
		auto it = find(name);
		if (it == player.end()) { cout << "none"; return; };
		for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++)
			cout << (*it1).name << ' ' << (*it1).year << ' ' << (*it1).genre;
		cout << endl;
	}

	void show() {
		for (auto i : player) {
			cout << i.first.name << ' ' << i.first.info << ' ' << i.first.beginyear << ' ' << i.first.country << ": ";
			for (auto it = i.second.begin(); it != i.second.end(); it++, cout << ", ")
				cout << (*it).name << ' ' << (*it).year << ' ' << (*it).genre;
			cout << endl;
		}
	}
};

Player player;

int main() {

	ifstream in("input.txt");
	setlocale(LC_ALL, "Russian");

	while (in.peek() != '-') {
		for (int i = 0; i < 3; i++) {
			singer a;
			song b;
			string s;
			char ch;
			getline(in, s, ',');
			a.name = s;
			getline(in, s, ',');
			a.info = s;
			getline(in, s, ',');
			a.beginyear = s;
			getline(in, s, ',');
			a.country = s;
			getline(in, s, ',');
			b.name = s;
			getline(in, s, ',');
			b.year = s;
			getline(in, s, ',');
			b.genre = s;
			player.add(a, b);
		}
	}
	
	int n;

	do {

		player.show();
		
		cout << endl;
		cout << "1) добавить исполнителя" << endl;
		cout << "2) удалить исполнителя" << endl;
		cout << "3) добавить исполнителю песню" << endl;
		cout << "4) удалить песню исполнителя" << endl;
		cout << "5) изменить песню исполнителя" << endl;
		cout << "6) изменить имя исполнителя" << endl;
		cout << "7) найти исполнителей, которые впервые были исполнены в промежутке лет" << endl;
		cout << "8) изменить информацию о исполнителе" << endl;
		cout << "9) удалить исполнителей, не исполняющих жанр" << endl;
		cout << "10) изменить год рождения исполнителя" << endl;
		cout << "11) удалить исполнителей, не исполнявших новых песен в последние n лет" << endl;
		cout << "12) найти песни, названия которых состоят из одного слова" << endl;
		cout << "13) изменить страну исполнителя" << endl;
		cout << "14) группа распалась" << endl;
        cout << "15) выход" << endl;

		std::cin >> n;

		switch (n) {
		case 1: {
			string s;
			singer temp;
			getline(cin, s);
			temp.name = s;
			player.add(temp);
			break;
			}
		case 2: {
			string s;
			singer temp;
			getline(cin, s);
			temp.name = s;
			player.erase(temp);
			break;
			}
		case 3: {
			string artname, songname;
			cin.get();
			getline(cin, artname);
			getline(cin, songname);
			song temp;
			temp.name = songname;
			player.add(artname, temp);
			break;
			}
		case 4: {
			string artname, songname;
			cin.get();
			getline(cin, artname);
			getline(cin, songname);
			player.erase_song(artname, songname);
			break;
			}
		case 5: {
			string artname, songname, newname;
			cin.get();
			getline(cin, artname);
			getline(cin, songname);
			getline(cin, newname);
			player.change_song(artname, songname, newname);
			break;
			}
		case 6: {
			string oldname, newname;
			cin.get();
			getline(cin, oldname);
			getline(cin, newname);
			player.change_name(oldname,newname);
			break;
			}
		case 7: {
			string y1, y2;
			cin >> y1 >> y2;
			player.search_song_by_year(y1, y2);
			system("pause");
			break;
			}
		case 8: {
			string name, info;
			cin.get();
			getline(cin, name);
			getline(cin, info);
			player.change_info(name, info);
			break;
			}
		case 9: {
			string genre;
			cin.get();
			getline(cin, genre);
			player.delete_if_no_genre(genre);
			break;
			}
		case 10: {
			string name, year;
			cin.get();
			getline(cin, name);
			cin >> year;
			player.change_year(name, year);
			break;
			}
		case 11: {
			int n;
			cin >> n;
			player.delete_if_no_songs(n);
			break;
			}
		case 12: {
			player.show_one_word();
			system("pause");
			break;
			}
		case 13: {
			string name, country;
			cin.get();
			getline(cin, name);
			getline(cin, country);
			player.change_country(name, country);
			break;
			}
		case 14: {
			string name, newartist;
			cin.get();
			getline(cin, name);
			getline(cin, newartist);
			player.if_break(name, newartist);
			break;
		    }
        case 15: {
            return 0;
            }
		}

		system("cls");

	} while (true);

}