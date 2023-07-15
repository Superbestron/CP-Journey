#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))

using namespace std;

const int MAX_N = 10;

int t, n, k, src, dest, memo[MAX_N][1 << (MAX_N - 1)];
bool dist[MAX_N][MAX_N];

int dp(int u, int mask) {
    if (!mask) {
        if (dist[u][0]) return 1;
        return 0;
    }
    int &ans = memo[u][mask];
    if (ans != -1) return ans;
    ans = 0;
    int m = mask;
    while (m) {
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        if (dist[u][v]) ans += dp(v, mask ^ two_pow_v);
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        memset(dist, true, sizeof dist);
        memset(memo, -1, sizeof memo);
        cin >> n >> k;
        for (int j = 0; j < k; j++) {
            cin >> src >> dest;
            dist[src - 1][dest - 1] = false;
            dist[dest - 1][src - 1] = false;
        }
        cout << "Case #" << i << ": " << dp(0, (1 << (n - 1)) - 1) / 2 % 9901 << '\n';
    }
}
