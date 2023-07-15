#include <bits/stdc++.h>

using namespace std;

int k, n;
long double memo[10][101];

long double dp(int prev, int digits) {
    if (prev < 0 || prev > k) return 0;
    if (digits == n) return 1;
    long double& ans = memo[prev][digits];
    if (ans != -1) return ans;
    ans = 0;
    ans += dp(prev - 1, digits + 1) + dp(prev, digits + 1) + dp(prev + 1, digits + 1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> k >> n) {
        long double ans = 0;
        fill(memo[0], memo[0] + 10 * 101, -1);
        for (int i = 0; i <= k; i++) {
            ans += dp(i, 1);
        }
        cout << fixed << setprecision(7) << 100.0 * ans / pow(k + 1, n) << '\n';
    }
}