#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string str; cin >> str;
    stack<int> s;
    unordered_map<int, pair<int, int>> m;
    set<string> set;
    int brackets = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            s.push(i);
            str[i] = '_';
        }
        else if (str[i] == ')') {
            m[brackets] = make_pair(s.top(), i);
            s.pop();
            brackets++;
            str[i] = '_';
        }
    }
    for (int i = 0; i < (1 << brackets) - 1; i++) {
        // add in brackets
        for (int j = 0; j < brackets; j++) {
            if (i & 1 << j) {
                pair<int, int> p = m[j];
                str[p.first] = '(';
                str[p.second] = ')';
            }
        }
        string temp;
        for (char c : str) {
            if (c != '_') temp += c;
        }
        set.insert(temp);
        // remove brackets
        for (int j = 0; j < brackets; j++) {
            if (i & 1 << j) {
                pair<int, int> p = m[j];
                str[p.first] = '_';
                str[p.second] = '_';
            }
        }
    }
    for (auto& s1 : set) cout << s1 << '\n';
}
