#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) {
    cin >> i;
  }
  int num = a[0], last = -1, ans = n;
  for (int i = 1; i < n; i++) {
    if (a[i] != num) {
      ans = min(ans, i - last - 1);
      last = i;
    }
  }
  ans = min(ans, n - last - 1);
  if (ans == n) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
