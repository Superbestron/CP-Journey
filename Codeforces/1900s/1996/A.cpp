#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

inline void solve() {
  cin >> n;
  if (n % 4 == 0) cout << n / 4 << '\n';
  else cout << 1 + (n - 2) / 4 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
