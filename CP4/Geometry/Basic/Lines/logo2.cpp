#include <bits/stdc++.h>
using namespace std;

// EPS of 1e-9 will WA
const double EPS = 1e-5;
const double two_pi = 2 * M_PI;

double DEG_to_RAD(double d) { return d * M_PI / 180.0; }

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

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y);            // return double
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n; cin >> t;
  string command, val;
  while (t--) {
    cin >> n;
    string unknown_command;
    vector<pair<string, int>> v;
    for (int i = 0; i < n; i++) {
      cin >> command >> val;
      if (val == "?") {
        unknown_command = command;
        v.emplace_back(command, -1);
      }
      else v.emplace_back(command, stoi(val));
    }
    if (unknown_command == "fd" || unknown_command == "bk") {
      // just simulate all commands except unknown command
      point curr(0, 0);
      double curr_rad = 0;
      for (auto &[cmd, num] : v) {
        if (num == -1) continue;
        if (cmd == "fd") {
          curr.x += num * cos(curr_rad);
          curr.y += num * sin(curr_rad);
        } else if (cmd == "bk") {
          curr.x -= num * cos(curr_rad);
          curr.y -= num * sin(curr_rad);
        } else if (cmd == "lt") {
          curr_rad = (curr_rad - DEG_to_RAD(num));
          if (curr_rad < 0) curr_rad += two_pi;
        } else {
          curr_rad = (curr_rad + DEG_to_RAD(num));
          if (curr_rad > two_pi) curr_rad -= two_pi;
        }
      }
      double dista = dist(point(0, 0), point(curr.x, curr.y));
      cout << static_cast<int>(round(dista)) << '\n';
    } else {
      for (int i = 0; i < 360; i++) {
        double to_turn = DEG_to_RAD(i);
        // just simulate all commands except unknown command
        point curr(0, 0);
        double curr_rad = 0;
        for (auto &[cmd, num] : v) {
          if (num == -1) {
            if (cmd == "lt") {
              curr_rad = (curr_rad - to_turn);
              if (curr_rad < 0) curr_rad += two_pi;
            } else {
              curr_rad = (curr_rad + to_turn);
              if (curr_rad > two_pi) curr_rad -= two_pi;
            }
            continue;
          }
          if (cmd == "fd") {
            curr.x += num * cos(curr_rad);
            curr.y += num * sin(curr_rad);
          } else if (cmd == "bk") {
            curr.x -= num * cos(curr_rad);
            curr.y -= num * sin(curr_rad);
          } else if (cmd == "lt") {
            curr_rad = (curr_rad - DEG_to_RAD(num));
            if (curr_rad < 0) curr_rad += two_pi;
          } else {
            curr_rad = (curr_rad + DEG_to_RAD(num));
            if (curr_rad > two_pi) curr_rad -= two_pi;
          }
        }
        if (fabs(curr.x) < EPS && fabs(curr.y) < EPS) {
          cout << i << '\n';
          goto done;
        }
      }
    }
    done:
    continue;
  }
}
