#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), pref(n);
  int mex = 0;
  for (int &i : a) cin >> i;
  unordered_set<int> s;
  for (int i = 0; i < n; i++) {
    s.insert(a[i]);
    while (s.count(mex)) mex++;
    pref[i] = mex;
  }
  mex = 0;
  s.clear();
  bool printed = false;
  for (int i = n - 1; i > 0; i--) {
    s.insert(a[i]);
    while (s.count(mex)) mex++;
    if (mex == pref[i - 1]) {
      cout << 2 << '\n';
      cout << 1 << ' ' << i << '\n';
      cout << i + 1 << ' ' << n << '\n';
      printed = true;
      break;
    }
  }
  if (!printed) cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
