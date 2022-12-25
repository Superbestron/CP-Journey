#include <iostream>
#include <math.h>

using namespace std;

int n, r, p;

long long recurse(long long* dp, long long x) {
    if (dp[x] != -1) return dp[x];
    if (x == 0 || x == 1) {
        return 0;
    }
    long long ans = r + (x - 1) * p;
    // i -> number of parts
    for (long long i = 2; i <= ceil(double(x) / 2); i++) {
        long long temp = recurse(dp, ceil((double(x) / i)));
        ans = min(ans, temp + r + (i - 1) * p);
    }

    dp[x] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> r >> p;
    long long dp[n + 1];
    fill(dp, dp + n + 1, -1);
    cout << recurse(dp, n);
}
