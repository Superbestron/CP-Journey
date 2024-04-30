#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k; k--;
  vi a(n);
  for (int &i : a) cin >> i;
  int x = find_if(a.begin(), a.end(), [&](int v) { return v > a[k]; }) - a.begin();
  vi pos(n);
  iota(pos.begin(), pos.end(), 0);
  int ans = 0;
  for (int i : {0, x}) {
    if (i == n) {
      continue;
    }
    swap(pos[i], pos[k]);
    vi stt(n);
    for (int j = 1, u = pos[0]; j < n; j++) {
      int v = pos[j];
      u = (a[u] > a[v] ? u : v);
      stt[u]++;
    }
    swap(pos[i], pos[k]);
    ans = max(ans, stt[k]);
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
