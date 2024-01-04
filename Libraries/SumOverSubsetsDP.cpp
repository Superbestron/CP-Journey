#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

const int OFFSET = 0;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vi arr(n), a(1 << n);
  for (int &i : arr) cin >> i;
  for (int i = 0; i < n; i++) {
    a[1 << i] = arr[i];
  }

// keeps track of the sum over subsets
// with a certain amount of matching bits in the prefix
  vector<vi> dp(1 << n, vi(n + 1));

  vi sos(1 << n);
  for (int mask = 0; mask < (1 << n); mask++) {
    dp[mask][-1 + OFFSET] = a[mask];
    for (int x = 0; x < n; x++) {
      dp[mask][x + OFFSET] = dp[mask][x - 1 + OFFSET];
      if (mask & (1 << x)) { dp[mask][x + OFFSET] += dp[mask - (1 << x)][x - 1 + OFFSET]; }
    }
    sos[mask] = dp[mask][n - 1 + OFFSET];
  }
}
