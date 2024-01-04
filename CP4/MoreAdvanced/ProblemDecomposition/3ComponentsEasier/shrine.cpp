#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const double EPS = 1e-9;

vi shrines;
int W, N, D, S;

inline double calculate_dist(int start, int end) {
  double theta = (double) abs(shrines[start] - shrines[end]) / N * 2 * M_PI;
  double dist = 2 * 1000 * sin(theta / 2);
  return dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> W) {
    if (W == 0) break;
    cin >> N >> D;
    vi divisors(D);
    shrines.clear();
    for (int &i : divisors) cin >> i;
    for (int i = 1; i <= N; i++) {
      for (int divisor : divisors) {
        if (i >= divisor && i % divisor == 0) {
          shrines.push_back(i);
          break;
        }
      }
    }
    S = shrines.size();
    double dist = 1e9;

    // Referenced from Brandon Tang
    // S / W due to symmetry
    // quite hard to prove but the main idea is that all choices are covered with S / W
    for (int fst_s = 0; fst_s < S / W; fst_s++) {
      double lo = 0, hi = 2000 * M_PI;
      while (fabs(hi - lo) > EPS) {
        double mid = (lo + hi) / 2;

        int cur_idx = fst_s, next_idx = (fst_s + 1) % S;
        int workers_used = 1;
        double cur_dist = 0;
        bool valid = true;
        while (next_idx != fst_s) {
          double next_length = calculate_dist(cur_idx, next_idx);
          if (cur_dist + next_length <= mid) {
            cur_dist += next_length;
          } else {
            cur_dist = 0;
            workers_used++;
          }
          cur_idx = next_idx;
          next_idx = (next_idx + 1) % S;

          if (workers_used > W) {
            valid = false;
            break;
          }
        }

        valid ? hi = mid : lo = mid;
      }
      dist = min(dist, lo);
    }

    cout << setprecision(1) << fixed << 2000 + dist << '\n';
  }
}
