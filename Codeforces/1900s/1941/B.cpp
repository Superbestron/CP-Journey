#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

inline void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  for (int i = 0; i < n - 2; i++) {
    int cnt = a[i];
    if (cnt < 0) {
      cout << "NO\n";
      return;
    }
    a[i + 1] -= cnt * 2;
    a[i + 2] -= cnt;
  }
  if (a[n - 2] != 0 || a.back() != 0) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
