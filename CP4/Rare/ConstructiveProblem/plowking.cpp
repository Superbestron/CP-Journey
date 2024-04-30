#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, m;
  cin >> n >> m;
  ll ans = 0, e = 1, i = 1;
  while (n - e < m - i + 1) {
    ans += i;
    i += e;
    e++;
  }
  for (ll j = m - (n - e) + 1; j <= m; j++) ans += j;
  cout << ans << '\n';
}
