#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;
string a, b, c;

void solve() {
  cin >> n >> a >> b >> c;
  bool can = false;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i] && b[i] != c[i] && a[i] != c[i]) {
      can = true;
      break;
    }
    if (a[i] == b[i] && b[i] != c[i]) {
      can = true;
      break;
    }
  }
  cout << (can ? "YES" : "NO" ) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
