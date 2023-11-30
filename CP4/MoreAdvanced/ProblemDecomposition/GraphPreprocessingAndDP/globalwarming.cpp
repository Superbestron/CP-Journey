#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

vector<vector<int>> AM;
vector<int> memo;
unordered_map<int, int> bm_to_idx;
int bm;

int dp(int mask) { // DP state = mask
  int &ans = memo[mask]; // reference/alias
  if (ans != -1) return ans; // this has been computed
  if (mask == 0) return 0; // all have been matched
  ans = 1e9; // init with a large value
  int two_pow_p1 = LSOne(mask); // speedup
  int p1 = __builtin_ctz(two_pow_p1); // p1 is first on bit
  int p1_actual = bm_to_idx[p1];
  int m = mask - two_pow_p1; // turn off bit p1
  while (m) {
    int two_pow_p2 = LSOne(m); // then, try to match p1
    int p2 = __builtin_ctz(two_pow_p2); // with another on bit p2
    int p2_actual = bm_to_idx[p2];
    ans = min(ans, AM[p1_actual][p2_actual] + dp(mask ^ two_pow_p1 ^ two_pow_p2));
    m -= two_pow_p2; // turn off bit p2
  }
  return ans; // memo[mask] == ans
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, p, q, c, cost = 0;
  cin >> n >> m;
  AM.assign(n, vector<int>(n, 1e9));
  for (int i = 0; i < m; i++) {
    cin >> p >> q >> c;
    p--; q--;
    AM[p][q] = c;
    AM[q][p] = c;
  }
  vector<int> dist(n, 1e9);
  queue<int> que;
  bool can = true;
  for (int i = 0; i < n; i++) {
    if (dist[i] != 1e9) continue;
    bm = 0;
    que.push(i);
    dist[i] = 0;
    int count = 0;

    // find connected component
    while (!que.empty()) {
      int u = que.front(); que.pop();
      bm |= (1 << count);
      // mapping from actual idx to bitmask idx
      bm_to_idx[count++] = u;
      for (int v = 0; v < n; v++) {
        int dt = AM[u][v];
        if (dt == 1e9) continue;
        if (dist[v] != 1e9) continue;
        dist[v] = dist[u] + 1;
        que.push(v);
      }
    }

    if (__builtin_popcount(bm) % 2) {
      can = false;
      break;
    }
    memo.assign(1 << count, -1);
    cost += dp((1 << count) - 1);
  }

  if (!can) cout << "impossible\n";
  else cout << cost << '\n';
}
