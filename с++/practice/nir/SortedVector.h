#pragma once
#include <iostream>
#include <vector>

using namespace std;

class SortedVectorException : public exception {
private:
	string str;
public:
	SortedVectorException(string massage) : str(massage) {}
	const char* what() const noexcept override {
		return str.c_str();
	}
};

template <typename T>
class SortedVector {
private:

	vector<T> vec;

	int Search(int l, int r, T key) {

		if (l == r) {
			throw SortedVectorException("SortedVectorException::Search - HAS NOT BEEN FOUND");
		}

		int m = (l + r) / 2;

		if (vec[m] == key)
			return m;
		else {

			if (key > vec[m])
				Search(m + 1, r, key);
			else
				Search(l, m, key);

		}
	}

public:

	SortedVector() {}

	int Size() {
		return vec.size();
	}

	void Add(T key) {
		vec.push_back(key);
		int cur = Size() - 1;
		while (cur != 0 && vec[cur] < vec[cur - 1]) {
			swap(vec[cur], vec[cur - 1]);
			cur--;
		}
	}

	int Search(T key) {
		return Search(0, Size()-1, key);
	}

	void Delete(T key) {
		int cur = Search(key);
		vec.erase(vec.begin() + cur);
	}

	void Show() {
		for (int i = 0; i < Size(); i++) {
			cout << vec[i] << " ";
		}
		cout << endl;
	}

	T operator[] (int i){
		return vec[i];
	}

};

class Student {
public:
	string name;
	int age;
	int id;
	Student(string name, int age, int id) : name(name), age(age), id(id) {};

	friend bool operator<(const Student& stud1, const Student& stud2) {
		if (stud1.name != stud2.name)
			return (stud1.name < stud2.name);
		else if (stud1.age != stud2.age)
			return stud1.age < stud2.age;
		else
			return stud1.id < stud2.id;
	}

	friend bool operator>(Student& stud1, Student& stud2) {
		if (stud1.name != stud2.name)
			return (stud1.name > stud2.name);
		else if (stud1.age != stud2.age)
			return stud1.age > stud2.age;
		else
			return stud1.id > stud2.id;
	}

	friend bool operator==(Student& stud1, Student& stud2) {
		return (stud1.name == stud2.name) && (stud1.age == stud2.age) && (stud1.id == stud2.id);
	}

};

