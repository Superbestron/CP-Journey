#include <bits/stdc++.h>
using namespace std;
typedef vector<double> vd;
typedef tuple<int, int, int> iii;

vector<vd> AM;
vector<iii> v;
int t, w, n;
const double EPS = 1e-9;

bool can(double val) {
  vector<int> left, right;
  for (int i = 0; i < n; i++) {
    auto &[x, y, r] = v[i];
    if (x - r <= val) left.push_back(i);
    if (w - (x + r) <= val) right.push_back(i);
  }
  vector<bool> visited(n);
  queue<int> q;
  for (int i : left) q.push(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v = 0; v < n; v++) {
      if (visited[v]) continue;
      if (AM[u][v] > val) continue;
      visited[v] = true;
      q.push(v);
    }
  }
  for (int i : right) {
    if (visited[i]) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> w >> n;
    AM.assign(n, vd(n));
    v.clear();
    for (int i = 0; i < n; i++) {
      int x, y, r;
      cin >> x >> y >> r;
      v.emplace_back(x, y, r);
    }
    for (int i = 0; i < n; i++) {
      auto &[x1, y1, r1] = v[i];
      for (int j = i + 1; j < n; j++) {
        auto &[x2, y2, r2] = v[j];
        AM[i][j] = AM[j][i] = max(0.0, hypot(x1 - x2, y1 - y2) - r1 - r2);
      }
    }
    double lo = 0, hi = w;
    while (fabs(hi - lo) > EPS) {
      double mid = (lo + hi) / 2;
      can(mid) ? hi = mid : lo = mid;
    }
    cout << setprecision(6) << fixed << max(0.0, lo / 2) << '\n';
  }
}
