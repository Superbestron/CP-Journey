#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

int t, n;

inline void solve() {
  cin >> n;
  vi v(n - 1), ans(n);
  for (int &i : v) cin >> i;
  ans[n - 1] = 1e9;
  for (int i = n - 2; i >= 0; i--)
    ans[i] = ans[i + 1] - v[i];
  for (int &i : ans) cout << i << ' ';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
