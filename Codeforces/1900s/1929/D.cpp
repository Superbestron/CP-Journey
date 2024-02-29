#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

// This is one of the harder DP Trees Questions I've done.
// Idea is dp[i] is the number of (non-empty) subsets of vertices of the subtree rooted at vertex i
// such that no 2 pairs of vertices are ancestors of each other.
// If vertex i has subtrees u1, u2, u3, dp[i] = (dp[u1] + 1) * (dp[u2] + 1) * (dp[u3] + 1)
// The extra 1 factor is to also account for empty subset of each subtree.
// BUT this could lead to an empty set at the end, but instead we just take vertex i.
// Naively, calling dp[i] might give us the answer BUT...
// We have undercounted quite a number of subsets...
// Imagine we have a subtree like this,
//          1
//         /|\
//        2 3 4
//       / \
//      5   6
//     / \
//    7   8
// We would not have counted subsets like {1, 2}. Thus, we would need to do this:
// ANS = dp[1] + dp[2] + ... + dp[8].
// For e.g. Counting dp[2] again allows us to pair all the subsets of dp[2] with {1},
// essentially forming dp[2] more valid subsets.
// But you might wonder, why do we only merge with {1}, and not {1, 3}?
// I claim this is not possible as this will lead to a invalid subset.
// Also why not {3, 4}? We would have already accounted this for when we do
// dp[1] = (dp[2] + 1) * (dp[3] + 1) * (dp[4] + 1)
// To illustrate further, dp[7] will also merge with {1} and only {1}, merging with {2}
// should have been accounted for in dp[2]. Merging with {5} is also accounted for in
// dp[2]
// In conclusion, for all subtrees, we can combine the valid subsets with {1} to form
// more valid subsets.

int t, n;
const int MOD = 998244353;

vector<vi> AL;
vll memo, visited;

ll dp(int u) {
  visited[u] = true;
  ll &ans = memo[u];
  if (ans != -1) return ans;
  ans = 1;
  for (int v : AL[u]) {
    if (visited[v]) continue;
    ans = (ans * (dp(v) + 1)) % MOD;
  }
  return ans;
}


void solve() {
  cin >> n;
  AL.assign(n, {});
  memo.assign(n, -1);
  visited.assign(n, 0);
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  dp(0);
  ll sum = 0;
  for (ll i : memo) {
    sum = (sum + i) % MOD;
  }
  cout << (sum + 1) % MOD << '\n';
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
