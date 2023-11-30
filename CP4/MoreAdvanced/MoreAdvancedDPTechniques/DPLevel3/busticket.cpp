#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> memo;
vector<int> trips;
int s, p, m, n;

ll dp(int trip) {
  if (trip == n) return 0;
  ll &ans = memo[trip];
  if (ans != -1) return ans;
  ans = 1e18;
  ans = min(ans, s + dp(trip + 1));  // take single ticket
  auto it = lower_bound(trips.begin(), trips.end(), trips[trip] + m);
  ans = min(ans, p + dp(distance(trips.begin(), it)));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> s >> p >> m >> n;
  trips.assign(n, 0);
  memo.assign(n + 1, -1);
  for (int &i : trips) cin >> i;
  cout << dp(0) << '\n';
}
