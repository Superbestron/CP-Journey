#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> iii;

// I'll be honest, I needed some help for this question as I had no idea how to not TLE as the time
// constraints were very tight. Initially I only had dp_not_b0 function but it turns out that we
// can speed things up with rides that have b == 0 (i.e. rides whose value will not diminish with
// number of rides). Apart from this constraint, the idea is very much like the knapsack 0-1 problem
// except that we can reuse a ride multiple times (till its value <= 0). For rides that have b == 0,
// we realise that we can try all possible combinations of rides since the value of the rides will
// remain unchanged. Thus the "ride" state is not important, where time saved is very critical
// for this solution to not TLE.

int N, a, b, t, Q, T;
vector<iii> b0_rides, b_not0_rides;
int memo[100][25001], memo2[25001];

inline int sum(iii &tup, int k) {
  if (get<1>(tup) == 0) return get<0>(tup);
  return get<0>(tup) - (k - 1) * (k - 1) * get<1>(tup);
}

int dp_b0(int time) {
  if (time == 0) return 0;
  int &ans = memo2[time];
  if (ans != -1) return ans;
  ans = 0;
  for (auto &[a1, b1, t1] : b0_rides) {
    if (time - t1 >= 0) ans = max(ans, a1 + dp_b0(time - t1));
  }
  return ans;
}

int dp_notb0(int rides, int time) {
  if (time == 0 || rides == N) return 0;
  int &ans = memo[rides][time];
  if (rides == b_not0_rides.size()) return dp_b0(time);
  if (ans != -1) return ans;
  ans = dp_notb0(rides + 1, time);  // choose not to take this ride at all
  int k = 1, cum = 0, cum_time = 0;
  while (true) {
    cum_time += get<2>(b_not0_rides[rides]);
    if (time - cum_time < 0) break;
    int s = sum(b_not0_rides[rides], k);
    if (s <= 0) break;
    cum += s;
    // try every possible combination of taking k times of this ride
    ans = max(ans, cum + dp_notb0(rides + 1, time - cum_time));
    k++;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b >> t;
    if (b == 0) b0_rides.emplace_back(a, b, t);
    else b_not0_rides.emplace_back(a, b, t);
  }
  cin >> Q;
  memset(memo, -1, sizeof memo);
  memset(memo2, -1, sizeof memo2);
  for (int i = 0; i < Q; i++) {
    cin >> T;
    cout << dp_notb0(0, T) << '\n';
  }
}
