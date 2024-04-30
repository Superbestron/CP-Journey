#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct point {
  ll x, y;;   // only used if more precision is needed
  point() { x = y = 0; }                      // default constructor
  point(ll _x, ll _y) : x(_x), y(_y) {}        // user-defined
  bool operator==(point other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  friend std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << ' ' << p.y << '\n';
    return os;
  }
};

struct vec {
  ll x, y;  // name: 'vec' is different from STL vector
  vec(ll _x, ll _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return {b.x - a.x, b.y - a.y};
}

ll cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the '> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) >= 0;
}

vector<point> CH_Andrew(vector<point> &Pts) {    // overall O(n log n)
  int n = Pts.size(), k = 0;
  vector<point> H(2 * n);
  sort(Pts.begin(), Pts.end());                  // sort the points by x/y
  for (int i = 0; i < n; ++i) {                  // build lower hull
    while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; --i) {       // build upper hull
    while ((k >= t) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x, y;
  char c;
  cin >> n;
  vector<point> P;
  for (int i = 0; i < n; i++) {
    cin >> x >> y >> c;
    if (c == 'N') continue;
    P.emplace_back(x, y);
  }
  vector<point> ans(CH_Andrew(P));
  ans.pop_back();
  cout << ans.size() << '\n';
  int idx = 0;
  ii curr = {1e10, 1e10};
  for (int i = 0; i < ans.size(); i++) {
    auto &[x1, y1] = ans[i];
    if (x1 < curr.first || (x1 == curr.first && y1 < curr.second)) {
      curr = {x1, y1};
      idx = i;
    }
  }
  for (int i = idx; i < ans.size(); i++) cout << ans[i];
  for (int i = 0; i < idx; i++) cout << ans[i];
}
