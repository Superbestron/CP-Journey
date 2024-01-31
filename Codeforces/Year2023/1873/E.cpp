#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, x;
    cin >> t;
    while (t--) {
        cin >> n >> x;
        int lo = 1, hi = 2e9;
        vector<int> v(n);
        for (int& i : v) cin >> i;
        while (lo < hi) {
            int mid = (hi - lo + 1) / 2 + lo;
            long long cost = 0;
            for (int i : v) {
                if (mid - i > 0) cost += (mid - i);
            }
            if (cost <= x) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << '\n';
    }
}