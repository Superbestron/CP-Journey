#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  vector<vi> memo(n + 1, vi(2, 1e9));
  for (int &i : a) cin >> i;
  memo[0][1] = memo[0][0] = 0;
  for (int i = 0; i < n; i++) {
    // take
    memo[i + 1][1] = min(memo[i + 1][1], memo[i][0] + a[i]);
    memo[i + 1][1] = min(memo[i + 1][1], memo[i][1] + a[i]);
    // don't take
    memo[i + 1][0] = min(memo[i + 1][0], memo[i][1]);
  }
  cout << min(memo[n][0], memo[n][1]) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
