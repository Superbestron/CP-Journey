#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k; cin >> t;
    while (t--) {
        long long ans = 0;
        cin >> n >> k;
        vector<int> v;
        for (int i = 1; i <= n / 2; i++) {
            v.push_back(n + 1 - i);
            v.push_back(i);
        }
        if (n % 2) v.push_back((n + 1) / 2);
//        for (int i = 0; i < n - k + 1; i++) {
//            long long mini = INT32_MAX, maxi = 0;
//            for (int j = 0; j < k; j++) {
//                mini = min(mini, static_cast<long long>(v[i + j]));
//                maxi = max(maxi, static_cast<long long>(v[i + j]));
//            }
//            ans = max(ans, mini + maxi);
//        }
//        cout << ans << endl;
        for (int i : v) cout << i << ' ';
        cout << endl;
    }
}