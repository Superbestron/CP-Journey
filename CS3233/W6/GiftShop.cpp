#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;

int n, m;
vi a;
vll memo;
const ll negINF = -2e18;

ll dp(int idx) {
  if (idx == n) return 0;
  ll &ans = memo[idx];
  if (ans != negINF) return ans;
  ll mx = a[idx], mn = a[idx];
  for (int i = idx + 1; i <= min(n, idx + m); i++) {
    mx = max(mx, (ll) a[i - 1]);
    mn = min(mn, (ll) a[i - 1]);
    ll sz = i - idx;
    ans = max(ans, dp(i) + sz * (mn + mx));
  }
  return ans;
}

void solve() {
  cin >> n >> m;
  a.assign(n, 0);
  memo.assign(n, negINF);
  for (int &i : a) cin >> i;
  cout << dp(0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
