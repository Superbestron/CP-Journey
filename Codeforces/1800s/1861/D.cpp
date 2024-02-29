#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), prefix(n), suffix(n);
  for (int &i : a) cin >> i;
  prefix[0] = 0;
  suffix[n - 1] = 0;

  for (int i = 1; i < n; i++) prefix[i] += prefix[i - 1] + (a[i - 1] <= a[i]);
  for (int i = n - 2; i >= 0; i--) suffix[i] += suffix[i + 1] + (a[i] >= a[i + 1]);

  int ans = suffix[0];
  for (int i = 0; i < n - 1; ++i) {
    ans = min(ans, 1 + prefix[i] + suffix[i + 1]);
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
