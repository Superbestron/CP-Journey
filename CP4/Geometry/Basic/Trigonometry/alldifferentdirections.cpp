#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
double DEG_to_RAD(double d) { return d * M_PI / 180.0; }

vector<string> split(string& s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
}

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

int main() {
  int n;
  string s;
  while (cin >> n && n != 0) {
    double sum_x = 0, sum_y = 0;
    vector<pair<double, double>> final_dests;
    cin.ignore();
    for (int i = 0; i < n; i++) {
      getline(cin, s);
      vector<string> v(split(s, ' '));
      double curr_x = stod(v[0]), curr_y = stod(v[1]);
      double curr_deg = stod(v[3]);  // East is 0 degrees
      for (int j = 4; j < v.size(); j += 2) {
        double val = stod(v[j + 1]);
        if (v[j] == "walk") {
          curr_x += val * cos(DEG_to_RAD(curr_deg));
          curr_y += val * sin(DEG_to_RAD(curr_deg));
        } else {
          curr_deg += val;
          if (curr_deg > 360) curr_deg -= 360;
          if (curr_deg < 0) curr_deg += 360;
        }
      }
      sum_x += curr_x;
      sum_y += curr_y;
      final_dests.emplace_back(curr_x, curr_y);
    }
    double avg_x = sum_x / n;
    double avg_y = sum_y / n;
    double worst_dist = 0;
    for (int i = 0; i < n; i++) {
      auto &[x1, y1] = final_dests[i];
      worst_dist = max(worst_dist, hypot(x1 - avg_x, y1 - avg_y));
    }
    cout << setprecision(2) << fixed << avg_x << ' ' << avg_y << ' ' << worst_dist << '\n';
  }
}
