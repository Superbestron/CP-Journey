#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t;

void solve() {
  string x, y, ans1, ans2;
  cin >> x >> y;
  int len = max(x.size(), y.size());
  reverse(x.begin(), x.end());
  reverse(y.begin(), y.end());
  while (x.size() < len) x += '0';
  while (y.size() < len) y += '0';
  bool x_win = true;
  int i = len - 1;
  for (; i >= 0; i--) {
    ans1 += x[i];
    ans2 += y[i];
    if (x[i] != y[i]) {
      if (x[i] < y[i]) x_win = false;
      break;
    }
  }
  i--;
  for (; i >= 0; i--) {
    if (x_win) {
      ans1 += min(x[i], y[i]);
      ans2 += max(x[i], y[i]);
    } else {
      ans2 += min(x[i], y[i]);
      ans1 += max(x[i], y[i]);
    }
  }
  cout << ans1 << '\n' << ans2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
