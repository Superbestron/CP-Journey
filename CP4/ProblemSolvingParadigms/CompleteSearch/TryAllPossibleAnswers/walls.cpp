#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    float r, x, y;
    int l, w, n, ans = INT32_MAX; cin >> l >> w >> n >> r;
    vector<unordered_set<int>> v;
    pair<float, float> walls[4];
    walls[0] = make_pair(-l / 2.0, 0);
    walls[1] = make_pair(l / 2.0, 0);
    walls[2] = make_pair(0, -w / 2.0);
    walls[3] = make_pair(0, w / 2.0);
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        unordered_set<int> s;
        for (int k = 0; k < 4; k++) {
            pair<float, float> p = walls[k];
            if ((p.first - x) * (p.first - x) + (p.second - y) * (p.second - y) <= r * r) {
                s.insert(k);
            }
        }
        if (!s.empty()) v.emplace_back(s);
    }
    for (int i = 0; i < v.size(); i++) {
        unordered_set<int> s = v[i];
        if (s.size() == 4) {
            cout << 1; return 0;
        }
        for (int j = i + 1; j < v.size(); j++) {
            unordered_set<int> s1 = s;
            for (int t : v[j]) s1.insert(t);
            if (s1.size() == 4) {
                ans = min(ans, 2);
            }
            for (int k = j + 1; k < v.size(); k++) {
                unordered_set<int> s2 = s1;
                for (int t : v[k]) s2.insert(t);
                if (s2.size() == 4) {
                    ans = min(ans, 3);
                }
                for (int m = k + 1; m < v.size(); m++) {
                    unordered_set<int> s3 = s2;
                    for (int t : v[m]) s3.insert(t);
                    if (s3.size() == 4) {
                        ans = min(ans, 4);
                    }
                }
            }
        }
    }
    if (ans == INT32_MAX) cout << "Impossible";
    else cout << ans;
}