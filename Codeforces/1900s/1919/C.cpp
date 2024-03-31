#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), b(1, 1e9), c(1, 1e9);
  for (int &i : a) cin >> i;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] <= b.back()) {
      b.push_back(a[i]);
    } else if (a[i] <= c.back()) {
      c.push_back(a[i]);
      if (c.back() < b.back()) swap(b, c);
    } else {
      b.push_back(a[i]); // always better to put to the smallest array
      ans++;
      if (c.back() < b.back()) swap(b, c);
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
