#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vector<string> v(n);
  for (auto &s : v) cin >> s;
  vector<vi> val(n + 1, vi(n + 1));
  vector<vi> left(n + 1, vi(n));
  vector<vi> right(n + 1, vi(n));
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      val[i][j + 1] = val[i][j];
      val[i][j + 1] ^= left[i][j];
      if (j != 0) val[i][j + 1] ^= right[i][j - 1]; // j - 1 because right[i][j] contains the "-1" of right[i][j - 1]
      int value = val[i][j + 1];
      if ((value ^ (v[i][j] - '0')) == 1) {
        if (j != 0) left[i + 1][j - 1] ^= 1;
        else left[i + 1][j] ^= 1;
        if (j != n - 1) right[i + 1][j + 1] ^= 1;
        else right[i + 1][j] ^= 1;
        ans++;
      }
      if (j != 0) left[i + 1][j - 1] ^= left[i][j];
      else left[i + 1][j] ^= left[i][j];
      if (j != n - 1) right[i + 1][j + 1] ^= right[i][j];
      else right[i + 1][j] ^= right[i][j];
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
