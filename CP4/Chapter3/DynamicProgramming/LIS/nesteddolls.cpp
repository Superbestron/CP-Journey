#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        vector<pair<int, int>> A(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i].first >> A[i].second;
        }
        int k = 0;
        vector<int> L(n), L_id(n);
        auto cmp = [](auto& p1, auto& p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first > p2.first;
        };
        sort(A.begin(), A.end(), cmp);

        for (int i = 0; i < n; i++) {
            int pos = upper_bound(L.begin(), L.begin() + k, A[i].second) - L.begin();
            L[pos] = A[i].second;
            if (pos == k) {
                k = pos + 1;
            }
        }
        cout << k << '\n';
    }
}
