#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<ll> vi;

int t, n, k;
vi a;
unordered_set<ll> s;
ll mx, mn;

void backtrack(int idx, ll val, int taken) {
  if (taken == k) {
    s.insert(val);
    mx = max(mx, val);
    mn = min(mn, val);
    return;
  }
  if (idx == n) {
    return;
  }
  int left = k - taken;
  for (int i = idx; i <= n - left; i++) {
    backtrack(i + 1, val + a[i], taken + 1);
  }
}

void solve() {
  cin >> n >> k;
  s.clear();
  mx = 0;
  mn = 1e18;
  a.assign(n, 0);
  ll sum = 0;
  for (ll &i : a) {
    cin >> i;
    sum += i;
  }
  bool flip = false;
  if (k > n / 2) {
    flip = true;
    k = n - k;
  }
  backtrack(0, 0, 0);
  if (flip) cout << s.size() << ' ' << sum - mn << '\n';
  else cout << s.size() << ' ' << mx << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
