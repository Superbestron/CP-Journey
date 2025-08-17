#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, a, b, c;

inline void solve() {
  cin >> a >> b >> c;
  int ans = 1e9;
  for (int i = 1; i <= 10; i++) {
    ans = min(ans, abs(b - i) + abs(a - i) + abs(c - i));
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
