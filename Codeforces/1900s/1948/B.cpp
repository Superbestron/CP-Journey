#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

ii split(int x) {
  return {x / 10, x % 10};
}

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  int prev = a[0];
  if (a[0] >= 10) {
    ii s = split(a[0]);
    if (s.first <= s.second) {
      prev = s.second;
    }
  }

  bool ans = true;
  for (int i = 1; i < n; i++) {
    bool can = false;
    if (a[i] >= 10) {
      ii s = split(a[i]);
      if (s.first <= s.second && s.first >= prev) {
        prev = s.second;
        can = true;
      }
    }
    if (!can && a[i] >= prev) {
      prev = a[i];
      can = true;
    }
    if (!can) {
      ans = false; break;
    }
  }
  if (ans) cout << "YES\n";
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
