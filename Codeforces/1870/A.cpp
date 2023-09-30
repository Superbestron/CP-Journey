#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k, x;
    cin >> t;
    while (t--) {
        cin >> n >> k >> x;
        if (k - 1 > x) {
            cout << -1 << '\n';
            continue;
        }
        // mex of x alr requires geo_sum
        int geo_sum = k * (k - 1) / 2;
//        if (geo_sum > x) {
//            cout << -1 << '\n';
//            continue;
//        }
        // need at least n numbers for mex to be k
        if (n < k) {
            cout << -1 << '\n';
            continue;
        }
        if (k == x) {
            cout << (n - k) * (k - 1) + geo_sum << '\n';
        } else {
            cout << (n - k) * x + geo_sum << '\n';
        }
    }
}

