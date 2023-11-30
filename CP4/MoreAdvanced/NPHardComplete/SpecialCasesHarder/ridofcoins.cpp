#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Need to identify that {1, 5, 10} is canonical while the inclusion of 25 is not
// Apply greedy algorithm on {1, 5, 10} while brute force every single possible number of 25-cent coins

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll P, N1, N5, N10, N25;
  cin >> P >> N1 >> N5 >> N10 >> N25;
  ll total = N1 + N5 * 5 + N10 * 10 + N25 * 25;
  ll coins = N1 + N5 + N10 + N25;
  if (total < P) {
    cout << "Impossible";
    return 0;
  }
  ll change = total - P, ans = -1;
  // try every possible no of 25-cent coins
  for (ll U25 = 0; U25 <= min(N25, change / 25); U25++) {
    ll curr_change = change;
    curr_change -= U25 * 25;
    ll U10 = min(N10, curr_change / 10);
    curr_change -= U10 * 10;
    ll U5 = min(N5, curr_change / 5);
    curr_change -= U5 * 5;
    ll U1 = curr_change;
    // valid combination of change
    if (U1 <= N1) {
      ans = max(ans, coins - U25 - U10 - U5 - U1);
    }
  }
  if (ans == -1) cout << "Impossible";
  else cout << ans;
}
