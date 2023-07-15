#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))

using namespace std;

const int MAX_N = 20;

int tc = 1, n, m, u, v, t, dist[MAX_N][MAX_N];
long long memo_left[MAX_N][1 << (MAX_N - 1)], memo_right[MAX_N][1 << (MAX_N - 1)];

long long dp_left(int u, int mask) {
    if (!mask) return dist[u][0];
    long long &ans = memo_left[u][mask];
    if (ans != -1) return ans;
    ans = 2e9;
    int m = mask;
    while (m) {
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        ans = min(ans, dist[u][v] + dp_left(v, mask ^ two_pow_v));
        m -= two_pow_v;
    }
    return ans;
}

long long dp_right(int u, int mask) {
    if (!mask) return dist[u][n - 1];
    long long &ans = memo_right[u][mask];
    if (ans != -1) return ans;
    ans = 2e9;
    int m = mask;
    while (m) {
        int two_pow_v = LSOne(m);
        int v = __builtin_ctz(two_pow_v) + 1;
        ans = min(ans, dist[u][v] + dp_right(v, mask ^ two_pow_v));
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        memset(dist, 63, sizeof dist);
        memset(memo_left, -1, sizeof memo_left);
        memset(memo_right, -1, sizeof memo_right);
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> t;
            dist[u][v] = t;
            dist[v][u] = t;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        long long curr = INT32_MAX;
        if (n == 3) {
            curr = 2 * (dist[0][1] + dist[1][2]);
            goto done;
        }
        for (int bm = 0; bm < (1 << (n - 2)); bm++) {
            // once we turn on (n - 2) / 2 cities
            if (__builtin_popcount(bm) != (n - 2) / 2) continue;
            int complement = (1 << (n - 2)) - 1 - bm;
            for (int i = 1; i < n - 1; i++) { // finish bm at i
                for (int j = 1; j < n - 1; j++) { // finish complement at j
                    // i and j should be in bm
                    if (!(bm & (1 << (i - 1)))) continue;
                    if (!(bm & (1 << (j - 1)))) continue;
                    // bm ^ (1 << (i - 1)) clears (i - 1)th bit (mark it as visited)
                    long long temp = dp_left(i, bm ^ (1 << (i - 1))) + dp_right(i, complement) +
                            dp_left(j, complement) + dp_right(j, bm ^ (1 << (j - 1)));
                    curr = min(curr, temp);
                }
            }
        }
        done: cout << "Case " << tc++ << ": " << curr << '\n';
    }
}
