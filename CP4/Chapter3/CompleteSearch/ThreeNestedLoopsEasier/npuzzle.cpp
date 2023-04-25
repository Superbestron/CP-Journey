#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    unordered_map<char, pair<int, int>> m;
    // preprocess
    char c = 'A';
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[c] = make_pair(i, j);
            c++;
        }
    }
    for (int i = 0; i < 4; i++) {
        cin >> s;
        for (int j = 0; j < 4; j++) {
            if (s[j] != '.') {
                pair<int, int> p = m[s[j]];
                ans += abs(p.first - i) + abs(p.second - j);
            }
        }
    }
    cout << ans;
}
