#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int N, M;
vector<ld> probs;
vector<vector<ld>> memo(1001, vector<ld>(1001, -1));

ld prob(int n, int m) {
  int idx = N + M - n - m;
  if (n == 0) return 0;
  if (m == 0) return 1;
  ld &ans = memo[n][m];
  if (ans > -0.5) return ans;
  return ans = probs[idx] * prob(n, m - 1) + (1 - probs[idx]) * prob(n - 1, m);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  ld val;
  for (int i = 0; i < N + M - 1; i++) {
    cin >> val;
    probs.push_back(val);
  }
  cout << setprecision(6) << fixed << prob(N, M);
}
