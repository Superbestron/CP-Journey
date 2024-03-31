#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a;
  set<int> s;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (s.count(x)) continue;
    s.insert(x);
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int idx = upper_bound(a.begin(), a.end(), a[i] + n - 1) - a.begin();
    ans = max(ans, idx - i);
  }
  cout << ans << '\n';
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
