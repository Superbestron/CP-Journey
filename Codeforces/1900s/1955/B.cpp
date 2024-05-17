#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, c, d;

void solve() {
  cin >> n >> c >> d;
  vll a(n * n), b(n * n);
  for (ll &i : a) {
    cin >> i;
  }
  sort(a.begin(), a.end());
  b[0] = a[0];
  for (int i = 1; i < n; ++i) {
    b[i] = b[i - 1] + c;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      b[i * n + j] = b[(i - 1) * n + j] + d;
    }
  }
  sort(b.begin(), b.end());
  if (a == b) cout << "YES\n";
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
