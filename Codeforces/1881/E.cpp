#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

int t, n;
vector<int> v(n);
vector<int> memo;

int dp(int idx) {
  if (idx == n) return 0;
  int& ans = memo[idx];
  if (ans != 1e9) return ans;
  if (idx + v[idx] < n) {
    ans = min(ans, dp(1 + idx + v[idx]));
  }
  ans = min(ans, 1 + dp(idx + 1));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n;
    v.assign(n, 0);
    memo.assign(n + 1, 1e9);
    for (int &i : v) cin >> i;
    cout << dp(0) << '\n';
  }
}