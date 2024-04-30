#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef long double ld;

const double INF = 1e9;
const double EPS = 1e-9;
int n, val;

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator<(point other) const {          // override < operator
    if (fabs(x - other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
};

inline void solve() {
  vector<point> P(n);
  int ans = 0;
  unordered_map<ld, int> mp;
  for (auto &[x, y] : P) cin >> x >> y;
  for (int i = 0; i < n; i++) {
    auto &[x1, y1] = P[i];
    for (int j = i + 1; j < n; j++) {
      auto &[x2, y2] = P[j];
      ld grad;
      if (x2 - x1 == 0) grad = 1e9;
      else grad = (ld) (y2 - y1) / (x2 - x1);
      mp[grad]++;
      ans = max(ans, mp[grad]);
    }
    mp.clear();
  }
  cout << ans + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n) {
    if (n == 0) break;
    solve();
  }
}
