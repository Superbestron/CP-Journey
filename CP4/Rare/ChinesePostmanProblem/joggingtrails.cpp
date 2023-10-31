#include <bits/stdc++.h>
using namespace std;
#define LSOne(S) ((S) & -(S))                    // important speedup

int N, M;                                           // max N = 8
int dist[16][16], memo[1 << 16];                // 1<<16 = 2^16

int dp(int mask) {                            // DP state = mask
  int &ans = memo[mask];                      // reference/alias
  if (ans != -1) return ans;                    // this has been computed
  if (mask == 0) return 0;                       // all have been matched
  ans = 1e8;                                     // init with a large value
  int two_pow_p1 = LSOne(mask);                  // speedup
  int p1 = __builtin_ctz(two_pow_p1);            // p1 is first on bit
  int m = mask ^ two_pow_p1;                       // turn off bit p1
  while (m) {
    int two_pow_p2 = LSOne(m);                   // then, try to match p1
    int p2 = __builtin_ctz(two_pow_p2);          // with another on bit p2
    ans = min(ans, dist[p1][p2] + dp(mask ^ two_pow_p1 ^ two_pow_p2));
    m ^= two_pow_p2;                             // turn off bit p2
  }
  return ans;                                    // memo[mask] == ans
}

int main() {
  int a, b, c;
  while (cin >> N && N != 0) {
    cin >> M;
    vector<int> in_deg(N);
    int ans = 0;
    fill(dist[0], dist[0] + 16 * 16, 1e8);
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < M; i++) {
      cin >> a >> b >> c;
      a--; b--;
      int cost = min(dist[a][b], c); // Edge case, might have multiple edges from A -> B
      dist[a][b] = dist[b][a] = cost; // Only save the min cost edge
      in_deg[a]++;
      in_deg[b]++;
      ans += c;
    }
    int mask = (1 << N) - 1; // initially all bits are on (unmatched)

    // Do APSP to find out shortest distances
    for (int k = 0; k < N; k++) {
      if (in_deg[k] % 2 == 0) mask ^= (1 << k); // flip this bit off
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
    cout << dp(mask) + ans << '\n';
  }
}