#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void insert(vector<int> &num, int n) {
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        num.push_back(m);
    }
}

void show(vector<int> a) {
    for (auto x : a)
        cout << x << ' ';
}

set<int> trans(int num) {
    set<int> a;
    while (num > 0) {
        a.insert(num % 10);
        num /= 10;
    }
    return a;
}

int main() {
    
    int n;
    cin >> n;

    vector<int> num;
    insert(num, n);

    for (int i = 0; i < num.size()-1; i++) {
        set<int> a = trans(num[i]);
        set<int> b = trans(num[i+1]);
        vector<int> ans;

        set_difference(a.begin(), a.end(),
            b.begin(), b.end(), back_inserter(ans));

        if (!ans.empty()) show(ans);
        else cout << "none";
        cout << endl;
    }
    
}