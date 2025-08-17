#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;

inline void solve() {
  cin >> n >> s;
  // brute force the number tgt
  ull ans = 1e16;
  for (int i = 0; i < n - 1; i++) {
    vi a;
    for (int j = 0; j < i; j++) a.push_back(s[j] - '0');
    a.push_back(10 * (s[i] - '0') + (s[i + 1] - '0'));
    for (int j = i + 2; j < n; j++) a.push_back(s[j] - '0');

    if (n <= 3) {
      for (int j = 0; j < (1 << (n - 2)); j++) {
        ull sum = 0, curr_sum = a[0];
        // loop through the ops
        for (int k = 0; k < n - 2; k++) {
          // multiply
          if ((j & (1 << k)) != 0) {
            curr_sum *= a[k + 1];
          } else {
            sum += curr_sum;
            curr_sum = a[k + 1];
          }
        }
        sum += curr_sum;
        ans = min(ans, sum);
      }
    } else {
      bool has_zero = false;
      for (int num : a) if (num == 0) has_zero = true;
      if (has_zero) {
        ans = 0;
        break;
      }
      ull sum = 0;
      for (int num : a) if (num != 1) sum += num;
      ans = min(ans, sum);
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
