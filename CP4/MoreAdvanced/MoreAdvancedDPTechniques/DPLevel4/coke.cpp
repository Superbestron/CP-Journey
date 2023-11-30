#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<vector<int>>> memo;
int t, C, n1, n5, n10, total;

// Interesting question... Learn to choose which parameter to "drop" and "recover" in the dp
// In this case, u1 can be "recovered"

int dp(int left, int u5, int u10) {
  if (left == 0) return 0;
  int u1 = total - (C - left) * 8 - u5 * 5 - u10 * 10;
  int &ans = memo[left][u5][u10];
  if (ans != -1) return ans;
  ans = 1e9;
  if (u5 == 0 && u10 == 0) return ans = left * 8;
  // use 1 5-cent and 3 1-cent coins
  if (u5 >= 1 && u1 >= 3) ans = min(ans, 4 + dp(left - 1, u5 - 1, u10));
  // use 2 5-cent coins
  if (u5 >= 2) ans = min(ans, 2 + dp(left - 1, u5 - 2, u10));
  // use 1 10-cent and 3 1-cent coins
  if (u10 >= 1 && u1 >= 3) ans = min(ans, 4 + dp(left - 1, u5 + 1, u10 - 1));
  // use 1 10-cent coin
  if (u10 >= 1) ans = min(ans, 1 + dp(left - 1, u5, u10 - 1));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> C >> n1 >> n5 >> n10;
    total = n1 + n5 * 5 + n10 * 10;
    memo.assign(C + 1, vector<vector<int>>(151, vector<int>(n10 + 1, -1)));
    cout << dp(C, n5, n10) << '\n';
  }
}
