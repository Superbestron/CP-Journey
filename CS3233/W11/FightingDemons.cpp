#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;

ll t, h, a, b;

inline void solve() {
  cin >> h >> a >> b;
  if (a > b) {
    cout << "Alice\n";
  } else if (a < b) {
    cout << "Bob\n";
  } else {
    if (h % (a + 1) == 0) cout << "Bob\n";
    else cout << "Alice\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
