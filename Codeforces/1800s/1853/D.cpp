#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int t, n, q, x;

inline void solve() {
  cin >> n;
  vi b(n);
  vii a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a.begin(), a.end());
  int l = 0, r = n - 1, sz = n;
  while (l <= r) {
    if ((a[r].first == n - l) ^ (a[l].first == n - 1 - r)) {
      if (a[r].first == n - l) { // this side means "n" in the new array
        b[a[r--].second] = sz--;
      } else { // this side means "0" in the new array
        b[a[l++].second] = -(sz--);
      }
    } else {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  for (int i : b) cout << i << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
