#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, x, y;

void solve() {
  cin >> n >> x >> y;
  vi a(x), diff;
  for (int &i : a) cin >> i;
  int ans = max(0, x - 2 + y);
  sort(a.begin(), a.end());
  for (int i = 0; i < x - 1; i++) {
    if (a[i] + 2 == a[i + 1]) ans++;
    diff.push_back(a[i + 1] - a[i]);
  }
  // edge case
  if (a.back() == n - 1 && a[0] == 1) ans++;
  if (a.back() == n && a[0] == 2) ans++;
  diff.push_back(n - (a.back() - a[0])); // O(n) diffs
  sort(diff.begin(), diff.end());
  // try all even first
  int left = y;
  for (int d : diff) {
    if (d == 2) continue;
    if (d % 2 == 0) {
      int needed = (d - 2) / 2;
      if (left >= needed) {
        left -= needed;
        ans += d / 2;
      } else {
        ans += left;
        left = 0; break;
      }
    }
  }
  if (left > 0) {
    for (int d : diff) {
      if (d == 2) continue;
      if (d % 2 == 1) {
        int needed = d / 2;
        if (left >= needed) {
          left -= needed;
          ans += needed;
        } else {
          ans += left;
          break;
        }
      }
    }
  }
  cout << min(n - 2, ans) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
