#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> v(N);
    unordered_map<int, vector<pair<int, int>>> m;
    int d = -536870913;
    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            int sum = v[i] + v[j];
            if (m[sum].size() == 2) continue; // answers below might reuse same number, keep alternative in case
            m[sum].emplace_back(v[i], v[j]);
        }
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            int diff1 = v[i] - v[j];
            int diff2 = v[j] - v[i];
            if (m.count(diff1)) {
                for (auto& p : m[diff1]) {
                    int prev1 = p.first, prev2 = p.second;
                    if (!(v[i] == prev1 || v[i] == prev2 || v[j] == prev1 || v[j] == prev2)) {
                        d = max(d, v[i]);
                    }
                }
            }
            if (m.count(diff2)) {
                for (auto& p : m[diff2]) {
                    int prev1 = p.first, prev2 = p.second;
                    if (!(v[i] == prev1 || v[i] == prev2 || v[j] == prev1 || v[j] == prev2)) {
                        d = max(d, v[j]);
                    }
                }
            }
        }
    }
    if (d == -536870913) cout << "no solution";
    else cout << d;
}