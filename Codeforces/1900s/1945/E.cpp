#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, x;

void solve() {
  cin >> n >> x;
  vi a(n);
  int idx;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == x) idx = i;
  }
  int l = 1, r = n + 1;
  while (r - l > 1) {
    int m =(l + r) / 2;
    if (a[m - 1] <= x) l = m;
    else r = m;
  }
  cout << 1 << '\n';
  cout << l << ' ' << idx + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
