#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, p1, p2, p3, p4;
vector<vector<vi>> memo(201, vector<vi>(201, vi(201, -1)));

void solve() {
  cin >> p1 >> p2 >> p3 >> p4;
  auto dp = [&](auto &&f, int p1, int p2, int p3) {
    if (p1 == 0 && p2 == 0 && p3 == 0) return 0;
    int &ans = memo[p1][p2][p3];
    if (ans != -1) return ans;
    ans = 0;
    if (p1) ans = max(ans, f(f, p1 - 1, p2, p3));
    if (p2) ans = max(ans, f(f, p1, p2 - 1, p3));
    if (p3) ans = max(ans, f(f, p1, p2, p3 - 1));
    if ((p1 + p2) % 2 == 0 && (p1 + p3) % 2 == 0) ans++;
    return ans;
  };
  cout << dp(dp, p1, p2, p3) + p4 / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
