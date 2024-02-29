#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vii a(m);
  for (auto &[x, y] : a) {
    cin >> x >> y;
    x--; y--;
  }
  sort(a.begin(), a.end());
  vi memo(n + 1);
  multiset<ii> left, right;
  int idx = 0;
  for (int i = 0; i < n; i++) {
    while (idx != m && a[idx].first == i) {
      auto &[x, y] = a[idx++];
      left.emplace(x, y);
      right.emplace(y, x);
    }
    if (!right.empty()) {
      auto &[y, x] = *prev(right.end());
      memo[y + 1] = max(memo[y + 1], (int) left.size() + memo[i]);
    }
    memo[i + 1] = max(memo[i + 1], memo[i]);
    while (!right.empty() && right.begin()->first == i) {
      auto &[y, x] = *right.begin();
      left.erase({x, y});
      right.erase({y, x});
    }
  }
  cout << memo[n] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
