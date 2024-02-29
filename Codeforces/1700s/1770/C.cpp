#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vll a(n);
  bool can = true;
  unordered_set<ll> s;
  for (ll &i : a) {
    cin >> i;
    if (s.count(i)) can = false;
    s.insert(i);
  }
  sort(a.begin(), a.end());
  if (!can) {
    cout << "NO\n";
    return;
  }
  for (int mod = 2; mod <= n / 2; mod++) {
    vll cnt(mod);
    for (int i = 0; i < n; ++i) {
      cnt[a[i] % mod]++;
    }
    if (*min_element(cnt.begin(), cnt.end()) >= 2) {
      can = false; break;
    }
  }
  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
