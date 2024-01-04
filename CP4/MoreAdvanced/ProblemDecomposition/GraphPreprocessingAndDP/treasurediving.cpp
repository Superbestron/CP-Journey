#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef tuple<int, int> ii;

vector<vector<int>> memo;
vector<vector<int>> cave_AM;
unordered_map<int, int> mp;

int dp(int u, int mask) { // mask = free coordinates
  if (mask == 0) return cave_AM[mp[u]][0]; // close the tour
  int &ans = memo[mp[u]][mask];
  if (ans != -1) return ans; // computed before
  ans = 1e9;
  int m = mask;
  while (m) { // up to O(n)
    int two_pow_v = LSOne(m); // but this is fast
    int v = __builtin_ctz(two_pow_v) + 1; // offset v by +1
    ans = min(ans, cave_AM[mp[u]][mp[v]] + dp(v, mask ^ two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m, a, b, l, i, air;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    vector<vector<ii>> AL(n);
    for (int j = 0; j < m; j++) {
      cin >> a >> b >> l;
      AL[a].emplace_back(b, l);
      AL[b].emplace_back(a, l);
    }
    cin >> i;
    vector<int> p;
    p.push_back(0);
    for (int j = 0; j < i; j++) {
      int val; cin >> val;
      p.push_back(val);
    }
    i++;  // take starting point as "idol"
    cave_AM.assign(i, vector<int>(i, 1e9)); // source and i idols

    for (int j = 0; j < i - 1; j++) {
      vector<int> dist(n, 1e9);
      priority_queue<ii, vector<ii>, greater<>> pq;
      dist[p[j]] = 0;
      pq.emplace(0, p[j]);
      while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, w] : AL[u]) {
          if (d + w >= dist[v]) continue;
          dist[v] = d + w;
          pq.emplace(dist[v], v);
        }
      }
      for (int k = j + 1; k < i; k++) {
        cave_AM[j][k] = cave_AM[k][j] = dist[p[k]];
      }
    }

    cin >> air;

    // try every possible combination of idols to take
    // omit the first bit because we must include source
    int idols_taken = 0;
    for (int bm = 1; bm < (1 << (i - 1)); bm++) {
      memo.assign(i + 1, vector<int>(1 << (i - 1), -1));
      mp.clear();
      if (__builtin_popcount(bm) <= idols_taken) continue;
      int ctr = 0;
      for (int m = bm; m; ctr++, m -= LSOne(m)) {
        int idx = __builtin_ctz(m) + 1;
        mp[ctr + 1] = idx;  // map bit index to AM index
      }
      int ans = dp(0, (1 << ctr) - 1);
      if (ans <= air) idols_taken = ctr;
    }
    cout << idols_taken << '\n';
  }
}
