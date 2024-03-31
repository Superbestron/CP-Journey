#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

struct Comp {
  bool operator() (const ii &a, const ii &b) {
    return a.first + a.second > b.first + b.second;
  };
};

void solve() {
  cin >> n;
  vi a(n), b(n);
  multiset<ii, Comp> c;

  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  for (int i = 0; i < n; i++) {
    c.emplace(a[i], b[i]);
  }
  ll ans = 0;
  while (!c.empty()) {
    // alice
    {
      auto it = c.begin();
      ans += it->first - 1;
      c.erase(it);
    }

    // bob
    if (c.empty()) break;
    {
      auto it = c.begin();
      ans -= it->second - 1;
      c.erase(it);
    }
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
