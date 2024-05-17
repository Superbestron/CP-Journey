#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, x;

inline void solve() {
  cin >> x;
  int ans = 0, val;
  for (int i = 1; i < x; i++) {
    int temp = gcd(x, i) + i;
    if (ans < temp) {
      ans = temp;
      val = i;
    }
  }
  cout << val << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
