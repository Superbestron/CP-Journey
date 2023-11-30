#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll memo[13], factorial[13];

ll dp(int n) {
  ll &ans = memo[n];
  if (ans != -1) return ans;
  if (n == 1) {
    return ans = 0;
  } else if (n == 2) {
    return ans = 1;
  } else return ans = (n - 1) * (dp(n - 1) + dp(n - 2));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  memset(memo, -1, sizeof memo);
  factorial[0] = 1;
  for (int i = 1; i <= 12; i++) factorial[i] = factorial[i - 1] * i;
  cin >> t;
  while (t--) {
    cin >> n;
    cout << dp(n) << '/' << factorial[n] << '\n';
  }
}
