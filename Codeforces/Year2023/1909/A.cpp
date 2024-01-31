#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vector<ii> a(n);
  int min_x = 200, max_x = -200, min_y = 200, max_y = -200;
  for (auto &[x, y] : a) {
    cin >> x >> y;
    min_x = min(min_x, x);
    max_x = max(max_x, x);
    min_y = min(min_y, y);
    max_y = max(max_y, y);
  }

  if (min_x < 0 && max_x > 0 && min_y < 0 && max_y > 0) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
