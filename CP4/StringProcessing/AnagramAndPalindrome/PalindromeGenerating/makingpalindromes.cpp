#include <bits/stdc++.h>

using namespace std;

int N, MOD = 1e9 + 7;
string S;
long long memo[200][200][200];

long long dp(int l, int r, int k) {
    if (k == N) {
        if (l <= r) return 0;
        else return 1;
    }
    if (r - l + 1 > (N - k) * 2) return 0;
    long long& ans = memo[l][r][k];
    if (ans != -1) return ans;
    ans = 0;
    if (l <= r) {
        if (S[l] == S[r]) {
            // choose to take s[l]
            ans = (ans + dp(l + 1, r - 1, k + 1)) % MOD;
            // everything else
            ans = (ans + (25 * dp(l, r, k + 1) % MOD) % MOD);
        } else {
            // choose to take s[l]
            ans = (ans + dp(l + 1, r, k + 1)) % MOD;
            // choose to take s[r]
            ans = (ans + dp(l, r - 1, k + 1)) % MOD;
            // everything else
            ans = (ans + (24 * dp(l, r, k + 1)) % MOD) % MOD;
        }
    } else {
        ans = (ans + (26 * dp(l, r, k + 1)) % MOD) % MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> S;
    memset(memo, -1, sizeof memo);
    cout << dp(0, N - 1, 0);
}