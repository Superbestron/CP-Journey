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
  vi a(n);
  for (int &i : a) cin >> i;
  deque<ii> d;
  ll cost = n;
  int idx_0;
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      idx_0 = i;
      break;
    }
  }
  vi new_a(a.begin() + idx_0, a.end());
  for (int i = 0; i < idx_0; i++) new_a.push_back(a[i]);
  d.emplace_back(0, n - 1);
  d.emplace_back(n, 1);

  ll ans = cost;
  for (int i = 1; i < n; i++) {
    auto &[mex_to_pop, cnt] = d.front();
    cost -= mex_to_pop;
    cnt--;
    if (cnt == 0) d.pop_front();
    int tot_cnt = 0;
    while (!d.empty() && get<0>(d.back()) >= new_a[i]) {
      auto &[m, ct] = d.back();
      tot_cnt += ct;
      cost -= (ll) ct * (m - new_a[i]);
      d.pop_back();
    }
    d.emplace_back(new_a[i], tot_cnt);
    if (get<0>(d.back()) == n) {
      auto &[num, cnt] = d.back();
      cnt++;
    } else {
      d.emplace_back(n, 1);
    }
    cost += n;
    ans = max(cost, ans);
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
