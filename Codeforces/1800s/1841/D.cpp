#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

inline void solve() {
  cin >> n;
  vii a(n), inter;
  for (auto &[x, y] : a) cin >> x >> y;
  for (int i = 0; i < n; i++) {
    auto &[l1, r1] = a[i];
    for (int j = i + 1; j < n; j++) {
      auto &[l2, r2] = a[j];
      if (max(l1, l2) <= min(r1, r2)) inter.emplace_back(min(l1, l2), max(r1, r2));
    }
  }
  int curr = 0, ans = 0;
  auto comp = [](ii &a, ii &b) {
    return get<1>(a) < get<1>(b);
  };
  sort(inter.begin(), inter.end(), comp);
  for (auto &[l, r] : inter) {
    if (l < curr) continue;
    curr = r + 1;
    ans++;
  }
  cout << n - ans * 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
