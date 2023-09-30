#include <bits/stdc++.h>
#define LSOne(S) S & (-S)

using namespace std;

int B, T, M, val;
vector<int> V, farmers;
vector<vector<int>> memo;

int dp(int idx, int mask) {
  int& ans = memo[idx][mask];
  if (ans != -1) return ans;
  ans = 0;
  if (idx == T) {
    for (int i = 0; i < B; i++) {
      if (!(mask & (1 << i))) ans += V[i];
    }
    return memo[idx][mask] = ans;
  }
  // if farmer can give a bean that Jack already has, he will do so
  if (mask & farmers[idx]) return memo[idx][mask] = dp(idx + 1, mask);
  int bm = farmers[idx];
  // otherwise choose a random bean to give Jack
  while (bm) {
    int two_pow_v = LSOne(bm);
    ans = max(ans, dp(idx + 1, mask ^ two_pow_v));
    bm -= two_pow_v;
  }
  return memo[idx][mask] = ans;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> B;
  V.assign(B, 0);
  for (int& i : V) cin >> i;
  cin >> T;
  farmers.assign(T, 0);
  memo.assign(T + 1, vector<int>(1050000, -1));
  for (int i = 0; i < T; i++) {
    cin >> M;
    int mask = 0;
    for (int j = 0; j < M; j++) {
      cin >> val; val--;
      mask |= (1 << val);
    }
    farmers[i] = mask;
  }
  cout << dp(0, 0);
}