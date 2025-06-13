#include <iostream>

using namespace std;

void print(int n) {

	for (int i = 0; i < n; i++)
		if (n % 2 == 0)
			cout << 1;
		else
			cout << 0;
	cout << endl;

}

void rec(int n, int i) {

	if (n > 1) {
		print(i);
		rec(n - 1, i + 1);
		print(i);
	}
	if (n == 1) {
		print(i);
	}
	
}

int main() {

	rec(4, 1);

}