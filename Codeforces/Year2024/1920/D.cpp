#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n, q;

void solve() {
  cin >> n >> q;
  vii ops, queries;
  ll sz = 0;
  vll nums, output(q);
  bool exceed = false;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    if (exceed) continue;
    if (x == 1) {
      sz++;
      nums.push_back(y);
    } else {
      ll max_multiply = 2e18 / sz;
      if (y > max_multiply) {
        exceed = true;
        sz += (sz * max_multiply);
        ops.emplace_back(x, max_multiply);
        continue;
      }
      else sz += (sz * y);
    }
    ops.emplace_back(x, y);
  }
  for (int i = 0; i < q; i++) {
    ll val;
    cin >> val;
    queries.emplace_back(val, i);
  }
  sort(queries.begin(), queries.end());

  for (int i = ops.size() - 1; i >= 0; i--) {
    auto &[op, x] = ops[i];
    if (op == 1) {
      sz--;
      while (!queries.empty()) {
        auto [num, idx] = queries.back();
        if (num <= sz) break;
        queries.pop_back();
        output[idx] = nums.back();
      }
      nums.pop_back();
    } else {
      sz /= (x + 1);
      auto it = upper_bound(queries.begin(), queries.end(), make_tuple(sz, 0));
      while (it != queries.end()) {
        auto &[num, idx] = *it;
        num = num % sz;
        if (num == 0) num += sz;
        it++;
      }
      sort(queries.begin(), queries.end());
    }

  }
  for (ll i : output) cout << i << ' ';
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
