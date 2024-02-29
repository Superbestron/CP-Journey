#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, k;

void solve() {
  cin >> n;
  vi c(n);
  for (int &i : c) cin >> i;
  for (int i = n - 2; i >= 0; i--) {
    c[i] = min(c[i], c[i + 1]);
  }
  cin >> k;
  int rem = k % c[0], ans = k / c[0];
  cout << ans << ' ';
  for (int i = 1; i < n; i++) {
    if (c[i] != c[i - 1]) {
      int cost = c[i] - c[i - 1];
      ans = min(ans, rem / cost);
      rem -= ans * cost;
    }
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
