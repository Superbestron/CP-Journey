#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int c, t, h, f, a, b;
  cin >> c;
  while (c--) {
    cin >> t >> h >> f;
    vector<int> dp(h + 1);
    vector<vector<int>> acorn(t, vector<int>(h + 1));
    // initialization
    for (int tree = 0; tree < t; ++tree) {
      cin >> a;
      for (int i = 0; i < a; i++) {
        cin >> b;
        acorn[tree][b] += 1;
      }
      dp[h] = max(dp[h], acorn[tree][h]);
    }

    for (int height = h - 1; height >= 0; --height)
      for (int tree = 0; tree < t; ++tree) {
        acorn[tree][height] +=
            max(acorn[tree][height + 1], // from this tree +1 above
                ((height + f <= h) ? dp[height + f] : 0)); // from tree at height + f
        dp[height] = max(dp[height], acorn[tree][height]); // update this too
      }
    cout << dp[0] << '\n'; // the solution is here
  }
}
