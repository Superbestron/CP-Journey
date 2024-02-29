#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<long long> a(n), b(n);
        for (long long& i : a) cin >> i;
        for (long long& i : b) cin >> i;
        long long sum_a = 0, sum_b = 0, min_a = INT32_MAX, min_b = INT32_MAX;
        for (int i = 0; i < n; i++) {
            sum_a += a[i];
            min_a = min(min_a, a[i]);
        }
        for (int i = 0; i < n; i++) {
            sum_b += b[i];
            min_b = min(min_b, b[i]);
        }
        long long first = sum_a + (n * min_b), second = sum_b + (n * min_a);
        cout << min(first, second) << '\n';
    }
}

