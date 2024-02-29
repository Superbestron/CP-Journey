#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;
vector<vector<vll>> memo;
vi a = {1, 10, 100, 1000, 10000};
const ll negINF = -2e18;

ll dp(int idx, int c, int changed) {
  if (idx == n) return 0;
  ll &ans = memo[idx][c][changed];
  if (ans != negINF) return ans;
  int curr = s[idx] - 'A';
  if (changed) {
    ans = max(ans, dp(idx + 1, max(curr, c), changed) + (c > curr ? -1 : 1) * a[curr]);
  } else {
    for (int new_curr = 0; new_curr < 5; new_curr++) {
      bool have_changed = curr != new_curr;
      ans = max(ans, dp(idx + 1, max(new_curr, c), have_changed) + (c > new_curr ? -1 : 1) * a[new_curr]);
    }
  }
  return ans;
}

inline void solve() {
  cin >> s;
  n = s.size();
  reverse(s.begin(), s.end());
  memo.assign(n, vector<vll>(5, vll(2, negINF)));
  cout << dp(0, 0, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
