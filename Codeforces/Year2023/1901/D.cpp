#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

void solve() {
  cin >> n;
  vector<int> v(n), prefix(n), suffix(n);
  for (int & i : v) cin >> i;
  prefix[0] = v[0], suffix[n - 1] = v[n - 1];
  for (int i = 1; i < n; i++) {
    prefix[i] = max(prefix[i - 1] + 1, v[i]);
  }
  for (int i = n - 2; i >= 0; i--) {
    suffix[i] = max(suffix[i + 1] + 1, v[i]);
  }
  int ans = 2e9;
  for (int i = 0; i < n; i++) {
    int temp = v[i];
    if (i > 0) temp = max(temp, 1 + prefix[i - 1] + n - i - 1);
    if (i < n - 1) temp = max(temp, 1 + suffix[i + 1] + i);
    ans = min(ans, temp);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
