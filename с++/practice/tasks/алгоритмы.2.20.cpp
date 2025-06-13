#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <ctime>
#include <string>

using namespace std;

class sound {
public:
	int high, duration;
};

void show(vector <sound> a) {
	for (auto it = a.begin(); it != a.end(); it++, cout << endl)
		cout << (*it).high << ' ' << (*it).duration;
}

bool pred(sound a, sound b) {
	return (a.duration == b.duration);
}

int main() {

	srand(time(NULL));

	vector<sound> melody;

	for (int i = 0; i < 30; i++) {
		sound temp;
		temp.high = rand() % 15;
		temp.duration = rand() % 15;
		melody.push_back(temp);
	}

	auto it = adjacent_find(melody.begin(), melody.end(), pred);
	if (it != melody.end())
		cout << (*it).high << ' ' << (*it).duration << " and " << (*(it + 1)).high << ' ' << (*(it + 1)).duration << endl;
	else
		cout << "no" << endl;
	cout << endl;

	show(melody);
}