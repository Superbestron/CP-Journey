#include <bits/stdc++.h>

using namespace std;

int t, p, n;
unsigned arr[100], dp[20000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> p >> n;
        memset(dp, -1, sizeof dp);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            // Initially I did from 0 to p - 1 and I realised why I was wrong
            // Doing backwards ensures we don't use the same coin more than once
            for (int j = p - 1; j >= 0; j--) {
                if (dp[j] == -1) continue;
                dp[j + arr[i]] = min(dp[j + arr[i]], dp[j] + 1);
            }
        }
        int i;
        for (i = p; dp[i] == -1; i++);
        cout << i << ' ' << dp[i] << '\n';
    }
}