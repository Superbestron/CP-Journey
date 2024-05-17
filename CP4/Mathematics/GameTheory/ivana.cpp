#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, ans = 0;
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  for (int i = 0; i < n; i++) a.push_back(a[i]);
  vector<vi> memo(2 * n, vi(2 * n, -1e9));
  auto dp = [&](auto &&f, int l, int r) {
    if (l > r) return 0;
    int &ans = memo[l][r];
    if (ans != -1e9) return ans;
    ans = -1e4;
    ans = max(ans, -f(f, l + 1, r) + (a[l] % 2 == 1));
    ans = max(ans, -f(f, l, r - 1) + (a[r] % 2 == 1));
    return ans;
  };
  for (int i = 0; i < n; i++) ans += ((a[i] % 2 == 1) - dp(dp, i + 1, i + n - 1)) > 0;
  cout << ans << '\n';
}
