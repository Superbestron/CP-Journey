#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int T, n;
vector<vector<int>> memo;

int dp(int idx, int cover) {
  if (idx == n) return 1;
  int &ans = memo[idx][cover];
  if (ans != -1) return ans;
  if (cover) {
    ans = max(ans, dp(idx + 1, 0));
  } else {
    ans = max(ans, dp(idx + 1, 1) + dp(idx + 1, 0));
  }
  return ans = ans % MOD;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    memo.assign(n, vector<int>(2, -1));
    cout << dp(0, 0) << '\n';
  }
}
