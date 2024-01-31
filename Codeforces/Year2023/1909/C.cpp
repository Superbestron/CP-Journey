#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

auto comparator = [](ii &i1, ii &i2) {
  return (get<1>(i1) - get<0>(i1)) > (get<1>(i2) - get<0>(i2));
};

void solve() {
  cin >> n;
  vi l(n), r(n), w(n);
  vii ans;
  set<int> r_set;
  for (int &i : l) cin >> i;
  for (int i = 0; i < n; i++) {
    cin >> r[i];
    r_set.insert(r[i]);
  }
  for (int &i : w) cin >> i;
  sort(l.begin(), l.end(), greater<>());
  sort(w.begin(), w.end());
  for (int i = 0; i < n; i++) {
    int l_idx = l[i];
    auto it = r_set.lower_bound(l_idx);;
    int r_idx = *it;
    r_set.erase(it);
    ans.emplace_back(l_idx, r_idx);
  }
  sort(ans.begin(), ans.end(), comparator);
  ll output = 0;
  for (int i = 0; i < n; i++) {
    ll curr = w[i];
    auto &[le, ri] = ans[i];
    output += curr * (ri - le);
  }
  cout << output << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
