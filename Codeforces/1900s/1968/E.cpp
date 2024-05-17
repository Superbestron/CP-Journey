#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

inline void solve() {
  cin >> n;
  cout << 1 << ' ' << 1 << '\n';
  cout << 2 << ' ' << 1 << '\n';
  for (int i = 3; i < n; i++) {
    cout << 1 << ' ' << i << '\n';
  }
  if (n > 2) {
    cout << n << ' ' << n << '\n';
  }
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
