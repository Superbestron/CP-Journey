#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  map<ll, ll> mp;
  for (int &i : a) {
    cin >> i;
    mp[i]++;
  }
  ll ans = 0, nums = 0;
  vll temp;
  for (auto &[num, cnt] : mp) {
    if (cnt >= 3) ans += cnt * (cnt - 1) * (cnt - 2) / 6LL;
    if (cnt >= 2) ans += (cnt * (cnt - 1) / 2) * nums;
    nums += cnt;
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
