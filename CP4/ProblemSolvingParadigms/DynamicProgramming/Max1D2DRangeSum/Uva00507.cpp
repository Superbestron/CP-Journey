#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    cin >> n;
    int curr = 0, val, best = 0, best_length = -1, best_start = 0, best_end = 0, start_idx = 1;
    for (int i = 1; i < n; i++) {
      cin >> val;
      curr += val;
      if (curr < 0) {
        curr = 0;
        start_idx = i + 1;
      } else {
        if (curr > best) {
          best = curr;
          best_length = i - start_idx + 1;
          best_start = start_idx, best_end = i;
        } else if (curr == best) {
          if (i - start_idx + 1 > best_length) {
            best_length = i - start_idx + 1;
            best_start = start_idx, best_end = i;
          }
        }
      }
    }
    if (best_end == 0)
      printf("Route %d has no nice parts\n", tc);
    else
      printf("The nicest part of route %d is between stops %d and %d\n", tc, best_start, best_end + 1);
  }
}
