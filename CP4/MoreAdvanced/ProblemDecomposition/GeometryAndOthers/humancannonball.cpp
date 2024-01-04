#include <bits/stdc++.h>
using namespace std;

int main() {
  double x1, y1, x2, y2;
  int n;
  cin >> x1 >> y1 >> x2 >> y2 >> n;
  vector<pair<double, double>> v;
  double AM[n][n];
  for (int i = 0; i < n; i++) {
    double x, y;
    cin >> x >> y;
    for (int j = 0; j < v.size(); j++) {
      auto &[x3, y3] = v[j];
      double dist = hypot(x - x3, y - y3);
      double time = dist / 5;
      double running_d = abs(dist - 50);
      time = min(time, 2 + running_d / 5);
      AM[i][j] = AM[j][i] = time;
    }
    v.emplace_back(x, y);
    AM[i][i] = 0;
  }
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);

  double ans = hypot(x1 - x2, y1 - y2) / 5;
  for (int i = 0; i < n; i++) {
    double src_to_i = hypot(x1 - v[i].first, y1 - v[i].second) / 5;
    for (int j = 0; j < n; j++) {
      double i_to_j = AM[i][j];
      double dist = hypot(v[j].first - x2, v[j].second - y2);
      double j_to_dest = dist / 5;
      double running_d = abs(dist - 50);
      j_to_dest = min(j_to_dest, 2 + running_d / 5);
      ans = min(ans, src_to_i + i_to_j + j_to_dest);
    }
  }
  cout << setprecision(3) << fixed << ans << '\n';
}
