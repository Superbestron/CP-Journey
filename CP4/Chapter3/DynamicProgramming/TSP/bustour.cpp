//#include <bits/stdc++.h>
//#define LSOne(S) (S & (-S))
//
//using namespace std;
//
//const int MAX_N = 11;
//
//int tc = 1, n, m, u, v, t, dist[MAX_N][MAX_N], memo[MAX_N][1 << (MAX_N - 1)];
//pair<int, int> coords[MAX_N];
//
//int dp(int u, int mask) {
//    if (!mask) return dist[u][0];
//    int &ans = memo[u][mask];
//    if (ans != -1) return ans;
//    ans = 2e9;
//    int m = mask;
//    while (m) {
//        int two_pow_v = LSOne(m);
//        int v = __builtin_ctz(two_pow_v) + 1;
//        ans = min(ans, dist[u][v] + dp(v, mask ^ two_pow_v));
//        m -= two_pow_v;
//    }
//    return ans;
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    while (cin >> n >> m) {
//        for (int i = 0; i < m; i++) {
//            cin >> u >> v >> t;
//        }
//        cout << "Case " << tc << ": " << 0 << '\n';
//        tc++;
//    }
//}
