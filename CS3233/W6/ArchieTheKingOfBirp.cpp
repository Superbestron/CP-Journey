#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll, ll> ii;
typedef vector<int> vi;
typedef vector<ll> vll;

int n, idx, c;

vector<vll> memo;
vector<ii> a;

ll dp(int idx, int taken) {
  if (idx == n) return 0;
  ll &ans = memo[idx][taken];
  if (ans != -1) return ans;
  auto &[i1, c1] = a[idx];
  ans = 0;
  if (taken == 1) {
    if (idx == n - 1 || (get<0>(a[idx + 1]) - 1) != i1) {
      ans = max(ans, c1 + dp(idx + 1, 1));
    }
    ans = max(ans, c1 + dp(idx + 1, 0));
  } else {
    ans = max(ans, dp(idx + 1, 0));
    ans = max(ans, dp(idx + 1, 1));
  }
  return ans;
}

void solve() {
  cin >> n;
  memo.assign(n, vll(2, -1));
  for (int i = 0; i < n; i++) {
    cin >> idx >> c;
    a.push_back({idx, c});
  }
  cout << max(dp(0, 0), dp(0, 1)) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
