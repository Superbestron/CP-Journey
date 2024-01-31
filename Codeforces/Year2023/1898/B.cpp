#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

ll t, n;

void solve() {
  cin >> n;
  vector<int> vect(n);
  for (int &i : vect) cin >> i;
  ll ans = 0;
  for (int i = n - 2; i >= 0; i--) {
    if (vect[i + 1] < vect[i]) {
      if (vect[i] % vect[i + 1] == 0) {
        ans += vect[i] / vect[i + 1] - 1;
        vect[i] = vect[i + 1];
      } else {
        int var = vect[i] / vect[i + 1];
        var++;
        ans += var - 1;
        vect[i] /= var;
      }
    }
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
