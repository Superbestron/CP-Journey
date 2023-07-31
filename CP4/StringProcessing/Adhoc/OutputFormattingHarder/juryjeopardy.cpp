#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    string s;
    cout << t << '\n';
    // u, r, d, l
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int i = 0; i < t; i++) {
        cin >> s;
        int direction = 1, r = 0, c = 0, min_r = 0, max_r = 0, max_c = 0;
        set<pair<int, int>> mp; // too lazy to hash manually
        for (char ch : s) {
            if (ch == 'B') direction = (direction + 2) % 4;
            else if (ch == 'L') direction = (direction + 3) % 4;
            else if (ch == 'R') direction = (direction + 1) % 4;
            r += directions[direction][0];
            c += directions[direction][1];
            min_r = min(r, min_r);
            max_r = max(r, max_r);
            max_c = max(c, max_c);
            mp.emplace(r, c);
        }
        vector<string> ans(max_r - min_r + 3, string(max_c + 2, '#'));
        for (auto& [p1, p2] : mp) ans[p1 - min_r + 1][p2] = '.';
        cout << max_r - min_r + 3 << ' ' << max_c + 2 << '\n';
        for (auto& str : ans) cout << str << '\n';
    }
}