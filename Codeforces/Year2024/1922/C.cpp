#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n, m;

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  cin >> m;
  vi prefix, suffix;
  prefix.push_back(0);
  suffix.push_back(0);
  for (int i = 0; i < n - 1; i++) {
    if (i == 0) {
      prefix.push_back(prefix.back() + 1);
    } else {
      if (abs(a[i] - a[i - 1]) < abs(a[i] - a[i + 1])) {
        prefix.push_back(prefix.back() + abs(a[i] - a[i + 1]));
      } else {
        prefix.push_back(prefix.back() + 1);
      }
    }
  }
  for (int i = n - 1; i > 0; i--) {
    if (i == n - 1) {
      suffix.push_back(suffix.back() + 1);
    } else {
      if (abs(a[i] - a[i + 1]) < abs(a[i] - a[i - 1])) {
        suffix.push_back(suffix.back() + abs(a[i] - a[i - 1]));
      } else {
        suffix.push_back(suffix.back() + 1);
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    if (x == y) cout << 0 << '\n';
    else if (x < y) {
      x--; y--;
      cout << prefix[y] - prefix[x] << '\n';
    }
    else {
      x = n - x;
      y = n - y;
      cout << suffix[y] - suffix[x] << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
