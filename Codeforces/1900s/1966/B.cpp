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
  vector<string> v(n);
  for (auto &s : v) cin >> s;
  if (v[0][0] == v.back().back() || v.back()[0] == v[0].back()) {
    cout << "YES\n";
    return;
  }
  char top_left = v[0][0], btm_left = v.back()[0];
  bool can = false;
  if (top_left == btm_left) {
    char other = 'B';
    if (top_left == 'B') other = 'W';
    for (int i = 0; i < n; i++) {
      if (v[i][0] == other) {
        can = true;
        break;
      }
    }
    for (int i = 0; i < n; i++) {
      if (v[i].back() == top_left) {
        can = true;
        break;
      }
    }
  } else {
    char other = 'B';
    if (top_left == 'B') other = 'W';
    for (int i = 0; i < m; i++) {
      if (v[0][i] == other) {
        can = true;
        break;
      }
    }
    for (int i = 0; i < m; i++) {
      if (v.back()[i] == top_left) {
        can = true;
        break;
      }
    }
  }
  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
