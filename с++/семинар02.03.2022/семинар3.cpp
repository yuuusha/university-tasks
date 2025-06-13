#include <iostream>

using namespace std;

struct point {
	double x, y;
};

struct point3d {
	double x, y, z;
};

double distance(double x, double y, double x1, double y1) {
	return sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
}

double distance(double x, double y, double z, double x1, double y1, double z1) {
	return sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) + (z1 - z) * (z1 - z));
}

double distance(point A, point B) {
	return distance(A.x, A.y, B.x, B.y);
}

double distance(point3d A, point3d B) {
	return distance(A.x, A.y, A.z, B.x, B.y, B.z);
}

int main() {

	point A = { 0,0 };
	point B = { 1,1 };
	point3d C = { 0,0,0 };
	point3d D = { 1,1,1 };
	cout << distance(0, 0, 1, 1) << endl;
	cout << distance(0, 0, 0, 1, 1, 1) << endl;
	cout << distance(A, B) << endl;
	cout << distance(C, D) << endl;

}