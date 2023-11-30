#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

int N, a, b;
vector<ii> v;
const int OFFSET = 400;
ll memo[40][801][801];

ll dp(int idx, int x, int y) {
  if (idx == v.size()) {
    return x == 0 && y == 0;
  }
  ll &ans = memo[idx][OFFSET + x][OFFSET + y];
  if (ans != -1) return ans;
  ans = 0;
  ans += dp(idx + 1, x, y);
  ans += dp(idx + 1, x + v[idx].first, y + v[idx].second);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    v.emplace_back(a, b);
  }
  memset(memo, -1, sizeof memo);
  cout << dp(0, 0, 0) - 1 << '\n';
}
