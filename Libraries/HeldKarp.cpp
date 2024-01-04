#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

vector<vector<int>> memo;
vector<vector<int>> dist;

int dp(int u, int mask) { // mask = free coordinates
  if (mask == 0) return dist[u][0]; // close the tour
  int &ans = memo[u][mask];
  if (ans != -1) return ans; // computed before
  ans = 2000000000;
  int m = mask;
  while (m) { // up to O(n)
    int two_pow_v = LSOne(m); // but this is fast
    int v = __builtin_ctz(two_pow_v) + 1; // offset v by +1
    ans = min(ans, dist[u][v] + dp(v, mask ^ two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int V, c;
  cin >> V;
  memo.assign(V, vector<int>(1 << (V - 1), -1));
  dist.assign(V, vector<int>(V));
  for (int i = 0; i < V; i++) {
    for (int j = i + 1; j < V; j++) {
      cin >> c;
      dist[i][j] = dist[j][i] = c;
    }
  }
  cout << dp(0, (1 << (V - 1)) - 1);
}