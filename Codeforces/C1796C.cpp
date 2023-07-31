#include <bits/stdc++.h>

using namespace std;

int inline sq_pow(int l, int r) {
    int ctr = 0;
    while (l <= r) {
        l <<= 1;
        ctr++;
    }
    return ctr - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, l, r;
    cin >> t;
    while (t--) {
        cin >> l >> r;
        int multiples = sq_pow(l, r);
        int ans = 0;
        cout << multiples + 1 << ' ';
        int le = l, ri = l * 2;
        while (le <= ri) {
            int mid = (le + ri) / 2;
            long long limit = mid << multiples;
            if (limit <= r) le = mid + 1;
            else ri = mid - 1;
        }
        ans += (le - l);
        le = l, ri = l * 2;
        while (le <= ri) {
            int mid = (le + ri) / 2;
            long long temp = mid << multiples;
            double limit = (double) temp * 1.5;
            if (limit <= r) le = mid + 1;
            else ri = mid - 1;
        }
        ans += multiples * (le - l);
        cout << ans << '\n';
    }
}