#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

void show(vector<char> a) {
    for (auto x : a)
        cout << x << ' ';
    cout << endl;
}

multiset<char> trans(string s) {
    multiset<char> a;
    for (int i = 0; i < s.size(); i++) {
        if (ispunct(s[i]))
            a.insert(s[i]);
    }
    return a;
}

int main() {
    
    set<char> punc = { ',', '.', '?', '!', '"', ';', ':', '-', '/'};

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        vector<char> ans;
        multiset<char> a = trans(s);

        set_difference(a.begin(), a.end(), punc.begin(), punc.end(), back_inserter(ans));

        auto it = unique(ans.begin(), ans.end());
        ans.erase(it, ans.end());
        show(ans);
    }
    
}
/*
ввод
1
???///.,!

вывод
/ ?

*/