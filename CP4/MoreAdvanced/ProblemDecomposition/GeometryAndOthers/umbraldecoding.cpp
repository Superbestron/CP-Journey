#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef tuple<int, int, int, int> iiii;

// Heavily referenced from Brandon Tang

bool inside(iii safe_pt, int x, int y) {
  auto &[p, q, b] = safe_pt;
  return abs(x - p) * abs(x - p) * abs(x - p) + abs(y - q) * abs(y - q) * abs(y - q) <= get<2>(safe_pt);
}

bool point_in_rect(iii pt, iiii &rect) {
  auto &[x, y, b] = pt;
  auto &[x1, y1, x2, y2] = rect;
  return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

ii get_closest_point(iii safe_pt, iiii &rect) {
  auto &[x0, y0, x1, y1] = rect;
  auto &[p, q, b] = safe_pt;

  int x, y;
  if (x0 <= p && p <= x1) x = p;
  else if (x0 > p) x = x0;
  else x = x1;

  if (y0 <= q && q <= y1) y = q;
  else if (y0 > q) y = y0;
  else y = y1;

  return {x, y};
}

vector<iii> umbrals;

ll recurse(iiii rect) {
  auto &[x0, y0, x1, y1] = rect;
  vector<ii> corners = {{x0, y0}, {x0, y1}, {x1, y0}, {x1, y1}};

  // if the entire rect is inside the umbra, just ignore
  for (auto &[p, q, b] : umbrals) {
    bool all_inside = true;
    for (auto &[x, y] : corners) {
      if (abs(x - p) + abs(y - q) > 1000 || !inside(make_tuple(p, q, b), x, y)) {
        all_inside = false;
        break;
      }
    }
    if (all_inside) return 0;
  }

  bool outside = true;
  // if the rect is completely outside the umbra, just add it
  for (auto &[p, q, b] : umbrals) {
    if (point_in_rect(make_tuple(p, q, b), rect)) {
      outside = false;
      break;
    }
    // check for obviously outside the umbra
    auto [lx, ly] = get_closest_point(make_tuple(p, q, b), rect);
    if (abs(lx - p) + abs(ly - q) <= 1000 && inside(make_tuple(p, q, b), lx, ly)) {
      outside = false;
      break;
    }
  }

  if (outside) return (ll) (x1 - x0 + 1) * (y1 - y0 + 1);

  // if the rect is partially inside the umbra, split it
  int half_x = (x0 + x1) / 2, half_y = (y0 + y1) / 2;
  ll ans = 0;
  ans += recurse(make_tuple(x0, y0, half_x, half_y));
  if (half_x + 1 <= x1) {
    ans += recurse(make_tuple(half_x + 1, y0, x1, half_y));
  }
  if (half_y + 1 <= y1) {
    ans += recurse(make_tuple(x0, half_y + 1, half_x, y1));
  }
  if (half_x + 1 <= x1 && half_y + 1 <= y1) {
    ans += recurse(make_tuple(half_x + 1, half_y + 1, x1, y1));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k, p, q, b;
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    cin >> p >> q >> b;
    umbrals.emplace_back(p, q, b);
  }
  ll ans = recurse(iiii(0, 0, n, n));
  cout << ans << '\n';
}
