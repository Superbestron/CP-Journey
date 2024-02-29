#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<ll, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

int t, n;
vector<vi> AL;
vi sz;

int dfs(int u) {
  int cnt = 1;
  for (int v : AL[u]) {
    cnt += dfs(v);
  }
  return sz[u] = cnt;
}

// k is number of vertices in current subtree that has already been matched
int dfs2(int u, int k) {
  int mx_subtree_sz = 0, idx;
  int sum = 0;
  for (int v : AL[u]) {
    if (mx_subtree_sz < sz[v]) {
      mx_subtree_sz = sz[v];
      idx = v;
    }
    sum += sz[v];
  }
  if (sum == 0) return 0;
  int remain_sum = sum - mx_subtree_sz;
  // can match all
  if (mx_subtree_sz - k <= remain_sum) {
    return (sum - k) / 2;
  } else {
    // -1 because we can use node u as part of the k matched
    return remain_sum + dfs2(idx, max(0, k + remain_sum - 1));
  }
}

void solve() {
  cin >> n;
  AL.assign(n, {});
  sz.assign(n, 0);
  for (int i = 1; i < n; i++) {
    int v;
    cin >> v; v--;
    AL[v].push_back(i);
  }
  dfs(0);
  cout << dfs2(0, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
