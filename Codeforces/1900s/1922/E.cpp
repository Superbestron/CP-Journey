#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

ll t, n;

void solve() {
  cin >> n;
  int m = 1;
  while ((1LL << m) < n) m++;
  if ((1LL << m) == n) {
    cout << m << '\n';
    for (int i = 0; i < m; i++) cout << i << ' ';
  } else {
    int i = 0;
    vi ans;
    m--;
    for (; i < m; i++) ans.push_back(i);
    ll remain = n - (1LL << m);
    while (remain > 0) {
      while ((1LL << m) > remain) m--;
      ans.insert(ans.begin() + m, i++);
      remain -= (1LL << m);
    }
    cout << ans.size() << '\n';
    for (ll a : ans) cout << a << ' ';
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
