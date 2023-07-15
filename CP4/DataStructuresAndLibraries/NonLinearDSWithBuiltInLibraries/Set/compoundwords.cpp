#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> v;
    set<string> set;
    while (cin >> s) v.emplace_back(s);
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (i != j) set.insert(v[i] + v[j]);
        }
    }
    for (auto& str : set) cout << str << endl;
}
