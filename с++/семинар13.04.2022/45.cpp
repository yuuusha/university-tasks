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
public:
    void add(T x)
    {
        Node* item = new Node(x);
        if (last != nullptr)
            last->next = item;
        last = item;
        if (first == nullptr)
            first = last;
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
        }

        tmp->next = nullptr;
        last = tmp;
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

};

int main() {
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(2);
    lst.add(2);
    List<int> newlst = lst.newlistwithoutX(2);
    newlst.print();

}