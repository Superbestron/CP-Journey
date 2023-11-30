#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> iii;

int main() {
  int n, t, xi, yi, ti;
  cin >> n >> t;
  vector<iii> v;
  int max_time = 0;
  for (int i = 0; i < n; i++) {
    cin >> xi >> yi >> ti;
    v.emplace_back(xi, yi, ti);
    max_time = max(ti, max_time);
  }
  vector<pair<double, double>> loc(max_time + 1);
  loc[0] = make_pair(get<0>(v[0]), get<1>(v[0]));
  double actual_dist = 0, recorded_dist = 0;
  for (int i = 0; i < n - 1; i++) {
    auto &[x1, y1, t1] = v[i];
    auto &[x2, y2, t2] = v[i + 1];
    double x_increment = (double) (x2 - x1) / (t2 - t1);
    double y_increment = (double) (y2 - y1) / (t2 - t1);
    double curr_x = x1, curr_y = y1;
    actual_dist += hypot(x2 - x1, y2 - y1);
    for (int time = t1 + 1; time <= t2; time++) {
      curr_x += x_increment, curr_y += y_increment;
      loc[time] = make_pair(curr_x, curr_y);
    }
  }
  for (int time = 0; time < max_time; time += t) {
    auto &[x1, y1] = loc[time];
    if (time + t > max_time) {
      auto &[x2, y2] = loc[max_time];
      recorded_dist += hypot(x2 - x1, y2 - y1);
    } else {
      auto &[x2, y2] = loc[time + t];
      recorded_dist += hypot(x2 - x1, y2 - y1);
    }
  }

  cout << setprecision(5) << fixed << fabs(actual_dist - recorded_dist) / actual_dist * 100 << '\n';
}
