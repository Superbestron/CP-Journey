#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;
string s;

inline void solve() {
  cin >> n;
  vector<int> v(n);
  for (auto &i:v) cin >> i;
  if (v[0] == 1) cout << "YES\n";
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
