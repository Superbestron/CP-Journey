#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> memo;
string s;

int dp(int l, int r) {
  if (l == r) return 1;
  if (l + 1 == r) {
    if (s[l] == s[r]) return 2;
    else return 1;
  }
  int &ans = memo[l][r];
  if (ans != -1) return ans;
  if (s[l] == s[r]) ans = max(ans, 2 + dp(l + 1, r - 1));
  else ans = max(ans, max(dp(l, r - 1), dp(l + 1, r)));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    cin >> s;
    memo.assign(1005, vector<int>(1005, -1));
    cout << dp(0, s.size() - 1) << '\n';
  }
}
