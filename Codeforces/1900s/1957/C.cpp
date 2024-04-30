#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, k;
const ll p = 1e9 + 7;

void solve() {
  cin >> n >> k;
  vll memo(n + 1, -1);
  auto fu = [&](auto &&f, ll num) -> ll {
    if (num == 1) return 1;
    if (num == 2) return 3;
    ll &ans = memo[num];
    if (ans != -1) return ans;
    ans = (ll) (2LL * (num - 1)) % p;
    ans = (ans * f(f, num - 2)) % p;
    ans = (ans + f(f, num - 1)) % p;
    return ans;
  };
  for (int i = 0; i < k; i++) {
    int r, c; cin >> r >> c;
    if (r == c) n--;
    else n -= 2;
  }
  if (n == 0) {
    cout << 1 << '\n';
    return;
  }
  cout << fu(fu, n) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
