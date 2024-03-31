#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, c;

void solve() {
  cin >> n >> c;
  vi a(n);
  for (int &i : a) cin >> i;
  ll x_plus_y = 0, y_minus_x = 0, inter = 0;
  int odds = 0, evens = 0;
  for (int i = 0; i < n; i++) {
    x_plus_y += (a[i] / 2) + 1;
    y_minus_x += (c - a[i] + 1);
    if (a[i] & 1) {
      inter += (odds + 1);
      odds++;
    } else {
      inter += (evens + 1);
      evens++;
    }
  }
  ll temp = x_plus_y + y_minus_x - inter;
  cout << (ll) (c + 1) * (c + 2) / 2 - temp << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
