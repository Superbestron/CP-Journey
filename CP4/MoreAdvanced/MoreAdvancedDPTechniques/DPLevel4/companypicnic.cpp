#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, double> ii;

vector<vector<int>> AL;
vector<vector<ii>> memo;
unordered_map<int, double> cost;
unordered_map<string, int> m;

ii dp(int u, int matched) {
  ii &ans = memo[u][matched];
  if (ans.first != -1) return ans;
  int teams = 0;
  double sums = 0;
  // child all don't match with current node
  for (int v : AL[u]) {
    auto [c_teams, c_sums] = dp(v, 0);  // don't take the child
    teams += c_teams;
    sums += c_sums;
  }
  ii best_ans = {teams, sums};

  // have a choice to match with a child node
  if (matched == 0) {
    int cur_teams;
    double cur_sums;
    for (int v : AL[u]) {
      ii temp = dp(v, 1);
      ii to_minus = dp(v, 0);
      cur_teams = teams + 1 + temp.first - to_minus.first;
      cur_sums = sums + min(cost[v], cost[u]) + temp.second - to_minus.second;
      best_ans = max(best_ans, {cur_teams, cur_sums});
    }
  }
  ans.first = best_ans.first;
  ans.second = best_ans.second;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, root;
  string low, high;
  double speed;
  cin >> n;
  memo.assign(n, vector<ii>(2, {-1, 0}));
  AL.assign(n, {});
  for (int i = 0; i < n; i++) {
    cin >> low >> speed >> high;
    if (!m.count(low)) m[low] = m.size();
    cost[m[low]] = speed;
    if (high == "CEO") {
      root = m[low];
      continue;
    }
    if (!m.count(high)) m[high] = m.size();
    AL[m[high]].push_back(m[low]);
  }

  ii ans = dp(root, 0);
  cout << ans.first << ' ';
  cout << setprecision(6) << fixed << ans.second / ans.first << '\n';
}
