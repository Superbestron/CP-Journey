#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))

using namespace std;

int t, x, y, n, memo[11][1 << 10];
pair<int, int> coords[11];

int dist(int source, int dest) {
    return abs(coords[source].first - coords[dest].first) + abs(coords[source].second - coords[dest].second);
}

int dp(int u, int mask) {
    if (!mask) return dist(u, 0);
    int &ans = memo[u][mask];
    if (ans != -1) return ans;
    ans = 2e9;
    int m = mask;
    while (m) {
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        ans = min(ans, dist(u, v) + dp(v, mask ^ two_pow_v));
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> x >> y;
        cin >> coords[0].first >> coords[0].second;
        cin >> n;
        n++;
        for (int i = 1; i < n; i++) {
            cin >> coords[i].first >> coords[i].second;
        }
        memset(memo, -1, sizeof memo);
        cout << dp(0, (1 << (n - 1)) - 1) << '\n';
    }
}
