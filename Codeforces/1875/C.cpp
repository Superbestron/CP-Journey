#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> pow2(30, 1);

bool IsPowerOfTwo(ll x) {
  return (x & (x - 1)) == 0;
}

pair<int, int> reduceFraction(int x, int y) {
  int d;
  d = gcd(x, y);

  x = x / d;
  y = y / d;

  return {x, y};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n, m;
  cin >> t;
  for (int i = 1; i < 30; i++) {
    pow2[i] = pow2[i - 1] * 2;
  }
  while (t--) {
    cin >> n >> m;
    pair<int, int> p = reduceFraction(n, m);
    ll x = p.first, y = p.second;
    if (y == 1) {
      cout << 0 << '\n';
      continue;
    }
    if (!IsPowerOfTwo(y)) {
      cout << -1 << '\n';
      continue;
    }
    ll ans = 0;
    n %= m;
    while (n) {
      ans += n;
      n *= 2;
      n %= m;
    }
    cout << ans << '\n';
  }
}