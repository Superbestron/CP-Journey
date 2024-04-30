#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  if (n == 1) {
    cout << k << '\n';
    return;
  }
  // n >= 2
  int two_pow = 1;
  while ((1LL << (two_pow + 1)) - 1 <= k) {
    two_pow++;
  }
  int curr = (1 << two_pow) - 1;
  cout << curr << ' ';
  cout << k - curr << ' ';
  for (int i = 2; i < n; i++) {
    cout << 0 << ' ';
  }
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
