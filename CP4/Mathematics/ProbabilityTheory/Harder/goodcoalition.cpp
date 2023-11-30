#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int T, N;
vector<pair<int, int>> probs;
vector<vector<ld>> memo;

ld dp(int id, int rem) {
  if (rem <= 0) return 1;
  if (id == N) return 0;
  ld &ans = memo[id][rem];
  if (ans > -0.5) return ans;
  return ans = max(dp(id + 1, rem), static_cast<ld>(probs[id].second) / 100 * dp(id + 1, rem - probs[id].first));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> N;
    memo.assign(N, vector<ld>(77, -1));
    probs.clear();
    for (int i = 0; i < N; i++) {
      int a, b;
      cin >> a >> b;
      probs.emplace_back(a, b);
    }
    cout << setprecision(6) << fixed << dp(0, 76) * 100 << '\n';
  }
}
