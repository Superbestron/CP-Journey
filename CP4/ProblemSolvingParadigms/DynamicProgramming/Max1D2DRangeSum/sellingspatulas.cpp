#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, time;
  double sales;
  while (cin >> n && n != 0) {
    vector<double> memo(1440, -0.08);
    for (int i = 0; i < n; i++) {
      cin >> time >> sales;
      memo[time] += sales;
    }

    double sum = 0, ans = 0;
    int start = 0, duration = 0, start_ans = 0, duration_ans = 0;
    for (int i = 0; i < 1440; i++) {
      sum += memo[i];
      // If making a loss, don't continue operating
      if (sum < EPS) {
        sum = 0;
        start = i + 1;
        duration = 0;
      } else {
        duration++;
      }

      if (sum - ans > EPS) {
        ans = sum;
        start_ans = start;
        duration_ans = duration;
      } else if (fabs(ans - sum) < EPS) {
        if (duration < duration_ans) {
          ans = sum;
          duration_ans = duration;
        }
      }
    }
    if (fabs(ans) < EPS) cout << "no profit\n";
    else cout << setprecision(2) << fixed << ans << ' ' << start_ans << ' ' << start_ans + duration_ans - 1<< '\n';
  }
}
