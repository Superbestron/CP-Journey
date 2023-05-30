#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ans = 0, k = 0;
    cin >> n;
    vector<int> A(n), L(n), L_id(n), LIS(n), LDS(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    // LDS
    for (int i = n - 1; i >= 0; i--) {
        int pos = lower_bound(L.begin(), L.begin() + k, A[i], greater()) - L.begin();
        L[pos] = A[i];
        LDS[i] = pos + 1;
        if (pos == k) {
            k = pos + 1;
        }
    }

    // LIS
    k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int pos = lower_bound(L.begin(), L.begin() + k, A[i]) - L.begin();
        L[pos] = A[i];
        LIS[i] = pos + 1;
        if (pos == k) {
            k = pos + 1;
        }
    }
    for (int i = 0; i < n; i++) {
        ans = max(ans, LIS[i] + LDS[i] - 1);
    }
    cout << ans << '\n';
}
