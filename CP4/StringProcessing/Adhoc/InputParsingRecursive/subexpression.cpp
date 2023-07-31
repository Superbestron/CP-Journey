#include <bits/stdc++.h>

using namespace std;

string s;
unordered_map<string_view, int> m;
vector<int> nesting_level;
int ctr;

// Impotant optimisations to avoid TLE/MLE
// 1. Use string_view instead of string to avoid redundant copies since we are not mutating the string in anyway
// 2. Calculate nesting once at the start of each test case rather than each call of parse

void parse(int l, int r) {
    string_view curr = string_view(s.data() + l, r - l + 1);
    if (m.count(curr)) {
        cout << m[curr];
        return;
    }
    m[curr] = ctr++;

    // single elem
    if (s[r] != ')') {
        cout << curr;
        return;
    }
    int comma = -1, left_b;
    for (int i = l; i <= r; i++) {
        if (nesting_level[i] == nesting_level[l] + 1) {
            if (s[i] == '(') left_b = i;
            else if (s[i] == ',') {
                comma = i;
                break;
            }
        }
    }

    cout << string_view(s.data() + l, left_b - l + 1);
    parse(left_b + 1, comma - 1);
    cout << ',';
    parse(comma + 1, r - 1);
    cout << ')';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ctr = 1;
        cin >> s;
        m.clear();
        nesting_level.assign(s.size(), 0);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') nesting_level[i] = nesting_level[i - 1] + 1;
            else if (s[i] == ')') nesting_level[i] = nesting_level[i - 1] - 1;
            else nesting_level[i] = nesting_level[i - 1];
        }
        parse(0, s.size() - 1);
        cout << '\n';
    }
}