#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, a, b, c;

void solve() {
  cin >> a >> b >> c;
  if (b % 3 != 0) {
    if (c + b % 3 < 3) {
      cout << -1 << '\n';
      return;
    }
  }
  cout << a + (b + c + 2) / 3 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
