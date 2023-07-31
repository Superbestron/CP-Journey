#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    char x; string temp, y;
    unordered_map<char, string> mp;
    for (int i = 0; i < n; i++) {
        cin >> x >> temp >> y;
        mp[x] = y;
    }
    cin >> y;
    for (int i = 0; i < m; i++) {
        temp.clear();
        for (char c : y) {
            if (mp.count(c)) {
                temp += mp[c];
            } else temp += c;
        }
        y = temp;
    }
    cout << y;
}