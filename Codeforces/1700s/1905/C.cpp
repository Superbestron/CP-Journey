#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n;
string s;

void solve() {
  cin >> n >> s;
  string stk;
  vi indices;
  for (int i = 0; i < n; i++) {
    while (!stk.empty() && s[i] > stk.back()) {
      stk.pop_back();
      indices.pop_back();
    }
    stk += s[i];
    indices.push_back(i);
  }
  int sz = stk.size(), ans = sz - 1;
  sort(stk.begin(), stk.end());
  // edge case here: if n repeated chars at back, we can save n - 1 of rotations
  for (int i = sz - 1; i >= 1; i--) {
    if (stk[i] == stk[i - 1]) ans--;
    else break;
  }
  for (int i = 0; i < sz; i++) {
    s[indices[i]] = stk[i];
  }
  if (is_sorted(s.begin(), s.end())) cout << ans << '\n';
  else cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
