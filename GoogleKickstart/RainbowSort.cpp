#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int T, N, colour;
    cin >> T;
    string encoding, s;
    auto cmp = [](pair<int, int>& p1, pair<int, int>& p2) {
        return p1.second < p2.second;
    };
    for (int t = 1; t <= T; t++) {
        cin >> N;
        int val = 1, prev = 0;
        bool possible = true;
        unordered_map<int, int> m;
        while (N--) {
            cin >> colour;
            if (!possible) continue;
            // if new colour
            if (m.count(colour) == 0) {
                m[colour] = val++;
            } else {
                if (m[colour] < prev) possible = false;
            }
            prev = m[colour];
        }
        cout << "Case #" << t << ": ";
        vector<pair<int, int>> v(m.begin(), m.end());
        sort(v.begin(), v.end(), cmp);
        if (possible) {
            for (auto& p : v) cout << p.first << ' ';
        } else {
            cout << "IMPOSSIBLE";
        }
        cout << '\n';
    }
}

