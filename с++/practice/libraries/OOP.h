#include <iostream>
#include <string>
using namespace std;

class DoubleListException {
private:
	string str;
public:
	DoubleListException(string massage) : str(massage) {}
	string what() {
		return str;
	}
};

class QueueException {
private:
	string str;
public:
	QueueException(string massage) : str(massage) {}
	string what() {
		return str;
	}
};

class ListException {
private:
	string str;
public:
	ListException(string message) : str(message) {}
	string what() {
		return str;
	}
};

template <class Item> class List {
	struct Element {
		Item inf;
		Element* next;
		Element(Item x) :inf(x), next(0) {};
	};
	Element* head;
	int size;
	Element* Find(int index) {
		if ((index < 1) || (index > size)) {
			return NULL;
		}
		else {
			Element* cur = head;
			for (int i = 1; i < index; i++) {
				cur = cur->next;
			}
			return cur;
		}
	}
public:
	List() : head(0), size(0) {}
	~List() {
		while (!Empty()) {
			Remove(1);
		}
	}
	bool Empty() {
		return head == 0;
	}
	int GetLength() {
		return size;
	}
	Item Get(int index) {
		if ((index < 1) || (index > size)) {
			throw ListException("ListException: get - list error");
		}
		else {
			Element* r = Find(index);
			Item i = r->inf;
			return i;
		}
	}
	void Insert(int index, Item data) {
		if ((index < 1) || (index > size + 1)) {
			throw ListException("ListException: insert - list error");
		}
		else {
			Element* newPtr = new Element(data);
			size = GetLength() + 1;
			if (index == 1) {
				newPtr->next = head;
				head = newPtr;
			}
			else {
				Element* prev = Find(index - 1);
				newPtr->next = prev->next;
				prev->next = newPtr;
			}
		}
	}
	void Remove(int index) {
		if ((index < 1) || (index > size)) {
			throw ListException("ListException: remove - list error");
		}
		else {
			Element* cur;
			--size;
			if (index == 1) {
				cur = head;
				head = head->next;
			}
			else {
				Element* prev = Find(index - 1);
				cur = prev->next;
				prev->next = cur->next;
			}
			cur->next = NULL;
			delete cur;
		}
	}
	void Print() {
		for (Element* cur = head; cur != NULL; cur = cur->next) {
			cout << cur->inf << ' ';
		}
		cout << endl;
	}
	int DeleteDuplicate() {
		int k = 0;
		for (int i = 1; i < GetLength(); i++) {
			if (Get(i) == Get(i + 1)) {
				Remove(i);
				k++;
				i--;
			}
		}
		return k;
	}
};

class Stack {
	struct Element {
		int inf;
		Element* next;
		Element(int x, Element* p) : inf(x), next(p) {}
	};
	Element* head;
public:
	Stack() : head(0) {}
	bool Empty() {
		return head == 0;
	}
	int Pop() {
		if (Empty()) {
			return 0;
		}
		Element* r = head;
		int i = r->inf;
		head = r->next;
		delete r;
		return i;
	}
	void Push(int data) {
		head = new Element(data, head);
	}
	int Top() {
		if (Empty()) {
			return 0;
		}
		else {
			return head->inf;
		}
	}
};

template <class Item>
class Queue {
	struct Element {
		Item inf;
		Element* next;
		Element(Item x) : inf(x), next(0) {}
	};
	Element* head, * tail;
public:
	Queue() : head(0), tail(0) {}
	bool Empty() {
		return head == 0;
	}
	Item Get() {
		if (Empty()) {
			throw QueueException("QueueException: get - queue empty");
		}
		else {
			Element* t = head;
			Item i = t->inf;
			head = t->next;
			if (head == NULL) {
				tail = NULL;
			}
			delete t;
			return i;
		}
	}
	void Put(Item data) {
		Element* t = tail;
		tail = new Element(data);
		if (!head) {
			head = tail;
		}
		else {
			t->next = tail;
		}
	}
};

template <class Item> class DoubleLinkedList {
	struct Element {
		Item inf;
		Element* next;
		Element* prev;
		Element(Item x) : inf(x), next(0), prev(0) {}
	};
	Element* head;
	Element* tail;
	int size;
	Element* Find(int index) {
		if ((index < 1) || (index > size)) {
			return NULL;
		}
		else {
			Element* cur = head;
			for (int i = 1; i < index; i++) {
				cur = cur->next;
			}
			return cur;
		}
	}
public:
	DoubleLinkedList() : head(0), tail(0), size(0) {}
	~DoubleLinkedList() {
		while (!Empty()) {
			Remove(1);
		}
	}
	bool Empty() {
		return head == 0;
	}
	int GetLength() {
		return size;
	}
	Item Get(int index) {
		if ((index < 1) || (index > size)) {
			throw DoubleListException("Exception: get - double-linked list error");
		}
		else {
			Element* r = Find(index);
			Item i = r->inf;
			return i;
		}
	}
	void InsertLeft(int index, Item data) {
		if ((index < 1) || (index > size + 1)) {
			throw DoubleListException("Exception: insert - double-linked list error");
		}
		else {
			Element* newPtr = new Element(data);
			size = GetLength() + 1;
			Element* cur = Find(index);
			if (cur == NULL) {
				head = newPtr;
				tail = newPtr;
			}
			else {
				newPtr->next = cur;
				newPtr->prev = cur->prev;
				cur->prev = newPtr;
				if (cur == head) {
					head = newPtr;
				}
				else {
					newPtr->prev->next = newPtr;
				}
			}
		}
	}
	void InsertRight(int index, Item data) {
		if ((index < 1 && head != NULL) || (index > size + 1)) {
			throw DoubleListException("Exception: insert — double-linked list error");
		}
		else {
			Element* newPtr = new Element(data);
			size = GetLength() + 1;
			Element* cur = Find(index);
			if (cur == NULL) {
				head = newPtr;
				tail = newPtr;
			}
			else {
				newPtr->next = cur->next;
				newPtr->prev = cur;
				cur->next = newPtr;
				if (cur == tail) {
					tail = newPtr;
				}
				else {
					newPtr->next->prev = newPtr;
				}
			}
		}
	}
	void Remove(int index) {
		if ((index < 1) || (index > size)) {
			throw DoubleListException("Exception: remove - double - linked list error");
		}
		else {
			Element* cur = Find(index);
			--size;
			if (size == 0) {
				head = NULL;
				tail = NULL;
			}
			else if (cur == head) {
				head = head->next;
				head->prev = NULL;
			}
			else if (cur == tail) {
				tail = tail->prev;
				tail->next = NULL;
			}
			else {
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
			}
			cur->next = NULL;
			cur->prev = NULL;
			delete cur;
		}
	}
	void PrintLeftToRight() {
		for (Element* cur = head; cur != NULL; cur = cur->next) {
			cout << cur->inf << ' ';
		}
		cout << endl;
	}
	void PrintRightToLeft() {
		for (Element* cur = tail; cur != NULL; cur = cur->prev) {
			cout << cur->inf << ' ';
		}
		cout << endl;
	}
};