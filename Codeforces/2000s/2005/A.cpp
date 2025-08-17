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
  string ans, temp = "aeiou";
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < n / 5; j++) {
      ans += temp[i];
    }
    if (n % 5 >= i + 1) ans += temp[i];
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
