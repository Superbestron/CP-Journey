#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, k;

void solve() {
  cin >> n >> m >> k;
  vi a(n), d(m), f(k), idxes, d_t(m);
  for (int &i : a) cin >> i;
  for (int &i : d) cin >> i;
  for (int &i : f) cin >> i;
  sort(f.begin(), f.end());
  int diff = 0, idx;
  priority_queue<int, vi, greater<>> pq;
  for (int i = 1; i < n; i++) {
    pq.push(a[i] - a[i - 1]);
    if (pq.size() > 2) pq.pop();
    if (a[i] - a[i - 1] > diff) {
      diff = a[i] - a[i - 1];
      idx = i - 1;
    }
  }
  int mx1 = diff, mx2 = 0;
  if (pq.size() == 2) {
    mx2 = pq.top();
  }
  int l = a[idx], r = a[idx + 1];
  int target = ((ll) l + r + 1) / 2;
  for (int i = 0; i < m; i++) {
    int val = d[i];
    auto bk = lower_bound(f.begin(), f.end(), target - val);
    if (bk == f.begin()) {
      if (*bk + val < r) mx1 = min(mx1, *bk + val - l);
      continue;
    }
    auto fr = prev(bk);
    if (*fr + val > l) mx1 = min(mx1, r - (*fr + val));
    if (bk != f.end()) {
      if (*bk + val < r) mx1 = min(mx1, *bk + val - l);
    }
  }
  cout << max(mx2, mx1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
