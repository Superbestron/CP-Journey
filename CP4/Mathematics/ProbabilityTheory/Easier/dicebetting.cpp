#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int n, s, k;
vector<vector<ld>> memo(10005, vector<ld>(501, -1));

ld prob(int rolls_left, int num_distinct_vals) {
  if (num_distinct_vals >= k) return 1;
  if (rolls_left == 0 || rolls_left < k - num_distinct_vals) return 0;

  if (memo[rolls_left][num_distinct_vals] != -1) return memo[rolls_left][num_distinct_vals];

  ld p_repeated = num_distinct_vals / (ld) s;
  ld p_different = 1 - p_repeated;

  return memo[rolls_left][num_distinct_vals] = p_repeated * prob(rolls_left - 1, num_distinct_vals)
      + p_different * prob(rolls_left - 1, num_distinct_vals + 1);
}
int main() {
  cin >> n >> s >> k;
  cout << setprecision(10) << fixed << prob(n, 0);
}