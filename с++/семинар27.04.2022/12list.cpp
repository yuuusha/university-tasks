#include <iostream>

using namespace std;

template <typename T>
class List
{
    struct Node
    {
        T inf;
        Node* next;
        Node(T x, Node* ref = nullptr) : inf(x), next(ref) {}
    } *first = nullptr, * last = nullptr;

    int size = 0;

public:
    void add(T x)
    {
        Node* item = new Node(x);
        if (last != nullptr)
            last->next = item;
        last = item;
        if (first == nullptr)
            first = last;
        size++;
    }
    void print()
    {
        for (Node* tmp = first; tmp != nullptr; tmp = tmp->next)
        {
            cout << tmp->inf << " ";
        }
        cout << '\n';
    }

    void doubleX(T x)
    {
        for (Node* tmp = first; tmp != nullptr; tmp = tmp->next)
        {
            if (tmp->inf == x)
            {
                Node* newItem = new Node(x, tmp->next);
                tmp->next = newItem;
                if (tmp == last)
                    last = tmp->next;
                tmp = tmp->next;
                size++;
            }
        }
    }

    bool empty() {
        return first == last;
    }

    void deleteX(T x) {
        if (empty()) return;

        add(!x);

        Node* tmp = first;

        for (Node* tmp1 = tmp->next; tmp1->next != nullptr; ) {

            if (tmp1->inf == x && tmp == first) {
                first = tmp1;
            }
            else if (tmp1->next->inf == x) {
                tmp->next = tmp1->next;
                tmp1 = tmp1->next;
                continue;
            }

            tmp = tmp->next;
            tmp1 = tmp1->next;
            size--;
        }

        tmp->next = nullptr;
        last = tmp;
        size--;
    }

    List newlistwithoutX(T x) {
        List<T> newlist;

        for (Node* tmp = first; tmp != nullptr; tmp = tmp->next) {
            newlist.add(tmp->inf);
            if (tmp->inf == x) {
                tmp = tmp->next;
                if (tmp == nullptr) break;
            }
        }
        return newlist;
    }

    T min() {
        T min = first->inf;

        for (Node* tmp = first; tmp != nullptr; tmp = tmp->next) {
            if (min > tmp->inf)
                min = tmp->inf;
        }
        return min;
    }

    //a
    void insert() {
        T min = this->min();

        if (first->inf == min) {
            Node* item1 = new Node(0);
            item1->next = first->next;
            first->next = item1;

            Node* item = new Node(0);
            item->next = first;
            first = item;
            
        }
        else {
            for (Node* tmp = first; tmp != nullptr; tmp = tmp->next) {
                if (tmp->next->inf == min) {
                    Node* item = new Node(0);
                    item->next = tmp->next;
                    tmp->next = item;

                    Node* item1 = new Node(0);
                    item1->next = item->next->next;
                    item->next->next = item1;

                    break;
                }
            }
        }
        size += 2;
    }

    int getsize() {
        return size;
    }

    int maxneg() {
        T max = min();

        for (Node* tmp = first; tmp != nullptr; tmp = tmp->next) {
            if (max < tmp->inf && tmp->inf < 0)
                max = tmp->inf;
        }
        return max;
    }

    //b
    void fromAvrToMax() {
        T max = maxneg();
        if (max >= 0 || size%2==0) { cout << "error" << endl; return; }
        Node* tmp = first;
        for (int i = 0; i < size / 2; i++)
            tmp = tmp->next;
        tmp->inf = max;
    }

};

int main() {
    List<int> lst;
    lst.add(2);
    lst.add(3);
    lst.add(4);
    lst.add(1);
    lst.add(-5);
    //a
    lst.insert();
    //b
    lst.fromAvrToMax();
    lst.print();

}