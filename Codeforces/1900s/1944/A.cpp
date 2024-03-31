#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

inline void solve() {
  cin >> n >> k;
  int curr = n - 1;
  if (k >= curr) {
    cout << 1 << '\n';
    return;
  }
  while (k - curr >= 0 && curr > 0) {
    k -= curr;
    curr--;
  }
  cout << curr + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
