#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(n), dist;
  for (int &i : a) cin >> i;
  for (int i = 1; i < n; i++) {
    dist.push_back(abs(a[i] - a[i - 1]));
  }
  sort(dist.begin(), dist.end());
  int ans = 0;
  for (int i = 0; i < n - k; i++) {
    ans += dist[i];
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
