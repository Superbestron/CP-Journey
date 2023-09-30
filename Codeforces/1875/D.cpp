#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> a;
vector<pair<int, int>> v;
unordered_map<int, int> m;
vector<ll> memo;

ll recurse(int hole_idx) {
  if (hole_idx == -1) return 0;
  ll& ans = memo[hole_idx];
  if (ans != 1e9) return ans;
  ans = INT32_MAX;
  for (int i = 0; i <= hole_idx; i++) {
    ll t = (v[i].second - 1) * (v[hole_idx].first + 1) + v[i].first;
    ans = min(ans, t + recurse(i - 1));
  }
  return memo[hole_idx] = ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    a.assign(n, 0);
    m.clear();
    for (int& i : a) {
      cin >> i;
      m[i]++;
    }
    int hole;
    memo.assign(5000, 1e9);
    v = vector<pair<int, int>>(m.begin(), m.end());
    sort(v.begin(), v.end());
    for (int i = 0; i <= 5000; i++) {
      if (!m.count(i)) {
        hole = i; break;
      }
    }
    if (hole == 0) {
      cout << 0 << '\n';
      continue;
    }
    int idx_below_hole = lower_bound(v.begin(), v.end(), make_pair(hole, 6000)) - v.begin() - 1;
    assert(hole != -1);
    cout << recurse(idx_below_hole) << '\n';
  }
}