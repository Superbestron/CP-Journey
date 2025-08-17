#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, x, y;

inline void solve() {
  cin >> x >> y;
  int temp = x ^ y;
//  cout << (x ^ y) << '\n';
  int ans = 1;
  for (int i = 0; i < 32; i++) {
    if ((temp & (1 << i)) == 0) ans <<= 1;
    else break;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
