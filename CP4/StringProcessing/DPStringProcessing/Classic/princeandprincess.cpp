#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, p, q; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> p >> q;
        int k = 0, P[p + 1], Q[q + 1];
        vector<int> A, L(max(p + 1, q + 1));
        unordered_map<int, int> m;
        for (int i = 0; i <= p; i++) {
            cin >> P[i];
            m[P[i]] = i;
        }
        for (int i = 0; i <= q; i++) {
            cin >> Q[i];
            if (!m.count(Q[i])) continue;
            A.push_back(m[Q[i]]);
        }
        for (int i : A) {
            int pos = lower_bound(L.begin(), L.begin() + k, i) - L.begin();
            L[pos] = i;
            if (pos == k) k = pos + 1;
        }
        printf("Case %d: %d\n", tc, k);
    }
}