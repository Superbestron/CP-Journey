#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

inline void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  int ans = 1e9;
  for (int i = 0; i < n - 1; i++) {
    int temp = max(a[i], a[i + 1]);
    ans = min(ans, temp - 1);
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
