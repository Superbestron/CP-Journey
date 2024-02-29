#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n, x, y;

void solve() {
  cin >> n >> x >> y;
  vi a(n);
  ll ans = 0;
  map<int, map<int, int>> mp;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = n - 1; i >= 0; i--) {
    int A = a[i] % x;
    int B = a[i] % y;
    ans += mp[(x - A) % x][B];
    mp[A][B]++;
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
