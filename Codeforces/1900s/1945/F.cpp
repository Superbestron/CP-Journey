#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), p(n);
  for (int &i : a) cin >> i;
  for (int &i : p) cin >> i;
  priority_queue<ii> pq;
  for (int i = 0; i < n; i++) {
    pq.emplace(a[i], i + 1);
  }
  ll sz = 1, curr_val = 0, ans = 0, ans_sz = 0;
  unordered_map<int, int> mp;
  unordered_set<int> removed;
  while (true) {
    while (mp.size() < sz && !pq.empty()) {
      auto [val, idx] = pq.top(); pq.pop();
      if (removed.count(idx)) continue; // cannot use because it is turned to 0
      mp[idx] = val;
      curr_val = val;
    }

    if (mp.size() < sz) break;

    ll product = (ll) curr_val * sz;
    if (product > ans) {
      ans = product;
      ans_sz = sz;
    }

    // remove
    if (mp.count(p[sz - 1])) mp.erase(p[sz - 1]);
    removed.insert(p[sz - 1]);
    sz++;
  }

  cout << ans << ' ' << ans_sz << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}