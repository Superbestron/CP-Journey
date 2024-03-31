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
  if (k == 1) {
    for (int i = 0; i < n; i++) {
      cout << i + 1 << ' ';
    }
  } else if (n != k) cout << -1;
  else {
    for (int i = 0; i < n; i++) {
      cout << 1 << ' ';
    }
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
