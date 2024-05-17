#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int t, n, m, k, d;

inline void solve() {
  cin >> n >> m >> k >> d;
  d++;
  vector<vll> a(n, vll(m));
  vll cols(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> a[i][j];
    vll memo(m, 1e18);
    multiset<ll> ms;
    memo[0] = 1;
    ms.insert(1);
    for (int j = 1; j < m; j++) {
      ll cost = *ms.begin() + a[i][j] + 1;
      memo[j] = cost;
      ms.insert(cost);
      if (j - d >= 0) {
        ms.erase(ms.find(memo[j - d]));
      }
    }
    cols[i] = memo.back();
  }
  ll sum = 0, ans = 1e18;
  for (int i = 0; i < k - 1; i++) sum += cols[i];
  for (int i = k - 1; i < n; i++) {
    sum += cols[i];
    ans = min(ans, sum);
    sum -= cols[i - (k - 1)];
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
