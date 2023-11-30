#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;

int n, m, k, gate, x, y;
vector<vector<int>> AL;
vector<bool> dest, in_deg;
ii memo[1000];

ii dp(int u) {
  if (AL[u].empty()) {
    return {dest[u], !dest[u]};
  }
  ii &ans = memo[u];
  if (ans.first != -1) return ans;
  ans.first = 0;
  for (int v : AL[u]) {
    ii temp = dp(v);
    ans.first += temp.first;
    ans.second += temp.second;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (auto &i : memo) {
    i = {-1, 0};
  }
  AL.assign(n, {});
  in_deg.assign(n, false);
  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    AL[x].push_back(y);
    in_deg[y] = true;
  }
  cin >> k;
  dest.assign(n, false);
  for (int i = 0; i < k; i++) {
    cin >> gate;
    dest[gate] = true;
  }
  ll wins = 0, losses = 0;
  for (int i = 0; i < n; i++) {
    if (!in_deg[i]) {
      ii temp = dp(i);
      wins += temp.first;
      losses += temp.second;
    }
  }
  printf("winning paths %lld\n", wins);
  printf("total paths %lld\n", wins + losses);
}
