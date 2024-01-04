#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int, int> iiii;
typedef pair<int, int> ii;

int n, m, max_cars;
vector<vi> AM, memo, memo2;

int dp2(int u, int mask) {
  if (mask == 0) return AM[u][n + 1];  // close up tour
  int &ans = memo2[u][mask];
  if (ans != -1) return ans;

  ans = 1e9;
  for (int bm = mask; bm; bm -= LSOne(bm)) {
    int two_pow_v = LSOne(bm);
    int idx = 1 + __builtin_ctz(two_pow_v);
    ans = min(ans, AM[u][idx] + dp2(idx, mask ^ two_pow_v));
  }
  return ans;  // begin the tour
}

// mask only includes cities 1 - n
int dp(int cars_used, int mask) {
  if (mask == 0) return 0;
  if (cars_used == max_cars) return 1e9;
  int &ans = memo[cars_used][mask];
  if (ans != -1) return ans;

  ans = 1e9;
  for (int subset = mask; subset; subset = (mask & (subset - 1))) {
    if (__builtin_popcount(subset) > 5) continue;
    int temp = max(dp2(0, subset) + __builtin_popcount(subset) * 5, dp(cars_used + 1, mask - subset));
    ans = min(ans, temp);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;

  AM.assign(n + 2, vi(n + 2, 1e9));
  for (int i = 0; i < m; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    // It's dam stupid, they have multiple roads from a to b
    AM[a][b] = AM[b][a] = min(AM[b][a], d);
  }

  for (int k = 0; k < n + 2; k++)
    for (int i = 0; i < n + 2; i++)
      for (int j = 0; j < n + 2; j++)
        AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);

  max_cars = (n + 4) / 5;
  memo.assign(max_cars, vi(1 << n, -1));
  memo2.assign(n + 1, vi(1 << n, -1));

  cout << dp(0, (1 << n) - 1) << '\n';
}
