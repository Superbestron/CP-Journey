#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, x;

void solve() {
  cin >> n;
  vi squares, mp(2 * n);
  for (int i = 0; i * i < 2 * n; i++) {
    squares.push_back(i * i);
  }
  mp[0] = 1;
  int prefix_xor = 0;
  ll odd = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;
    prefix_xor ^= x;
    for (int sq : squares) {
      if ((prefix_xor ^ sq) >= 2 * n) continue;
      odd += mp[prefix_xor ^ sq];
    }
    mp[prefix_xor]++;
  }
  cout << (ll) n * (n + 1) / 2 - odd << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
