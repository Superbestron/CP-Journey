#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    vector<pair<int, int>> v;
    for (int i = 0; i < 3; i++) {
        cin >> h >> w;
        v.emplace_back(h, w);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            vector<pair<int, int>> v2;
            pair<int, int> r1 = v[i];
            pair<int, int> r2 = v[j];
            if (r1.first == r2.first) {
                v2.emplace_back(r1.first, r1.second + r2.second);
            }
            if (r1.first == r2.second) {
                v2.emplace_back(r1.first, r1.second + r2.first);
            }
            if (r2.first == r1.second) {
                v2.emplace_back(r2.first, r2.second + r1.first);
            }
            if (r2.first == r1.second) {
                v2.emplace_back(r2.first, r2.second + r1.first);
            }
            int k = 3 - i - j;
            pair<int, int> r3 = v[k];
            for (auto& p : v2) {
                if (p.first == r3.first) {
                    if (p.first == p.second + r3.second) {
                        cout << "YES"; return 0;
                    }
                }
                if (p.first == r3.second) {
                    if (p.first == p.second + r3.first) {
                        cout << "YES"; return 0;
                    }
                }
                if (r3.first == p.second) {
                    if (r3.first == r3.second + p.first) {
                        cout << "YES"; return 0;
                    }
                }
                if (r3.first == p.second) {
                    if (r3.first == r3.second + p.first) {
                        cout << "YES"; return 0;
                    }
                }
            }
        }
    }
    cout << "NO";
}
