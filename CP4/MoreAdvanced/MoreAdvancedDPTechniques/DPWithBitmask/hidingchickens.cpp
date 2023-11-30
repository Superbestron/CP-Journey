#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef pair<double, double> ii;

int N;
double x, y, a, b;
vector<ii> coords;
double memo[1 << 20];

double dp(int mask) {
  if (mask == 0) return 0;
  double &ans = memo[mask];
  if (ans > -0.5) return ans;
  // go to next location and come back
  int two_pow = LSOne(mask);
  int next_hole_idx = __builtin_ctz(mask);
  ii &curr_coord = coords[next_hole_idx];
  ans = 2 * hypot(x - curr_coord.first, y - curr_coord.second) + dp(mask ^ two_pow);
  int m = mask;
  m -= two_pow;
  while (m) {
    // go to 2 locations before coming back
    int two_pow_other = LSOne(m);
    int other_hole_idx = __builtin_ctz(two_pow_other);
    ii &other_coord = coords[other_hole_idx];
    ans = min(ans, hypot(x - curr_coord.first, y - curr_coord.second)
        + hypot(curr_coord.first - other_coord.first, curr_coord.second - other_coord.second)
        + hypot(other_coord.first - x, other_coord.second - y) + dp(mask ^ two_pow ^ two_pow_other));
    m -= two_pow_other;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> x >> y >> N;
  fill(memo, memo + (1 << N), -1);
  double furthest = 0;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    coords.emplace_back(a, b);
    furthest = max(furthest, hypot(a - x, b - y));
  }
  cout << setprecision(6) << fixed << dp((1 << N) - 1) - furthest << '\n';
}
