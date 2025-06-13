#include <iostream>

using namespace std;

void print(int zv, int pr) {

	for (int i = 0; i < pr; i++) {
		cout << " ";
	}
	for (int i = 0; i < zv; i++) {
		cout << "*";
	}
	cout << endl;
}

void print(int pr) {

	for (int i = 0; i < pr; i++) {
		cout << " ";
	}

}

void tree(int n, int m, int i = 1) {

	print(m);
	print(i,n-i/2);
	if (i < 2*n+1)
		tree(n, m, i + 2);

}

void treee(int n, int i = 1) {

	if (i <= n) {
		tree(i,n-i);
		treee(n, i + 1);
	}

}

int main() {
   
	treee(2);

}