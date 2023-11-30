#include <bits/stdc++.h>
using namespace std;

int N, K, total = 0;
int rooms[201][2];
// 3 states per row, (open, open), (close, open), (open, close)
int memo[201][3][201];

int dp(int idx, int state, int covered) {
  if (idx == N) {
    if (covered == K) return 0;
    else return 1e9;
  }
//  if (((idx - N) << 1) < (K - covered)) return 1e9;
  int &ans = memo[idx][state][covered];
  if (ans != -1) return ans;
  ans = 1e9;
  ans = min(ans, dp(idx + 1, 0, covered));
  if (state != 1) ans = min(ans, rooms[idx][1] + dp(idx + 1, 2, covered + 1));
  if (state != 2) ans = min(ans, rooms[idx][0] + dp(idx + 1, 1, covered + 1));
  return ans;
}

int main() {
  cin >> N >> K;
  memset(memo, -1, sizeof memo);
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j < 2; j++) {
      cin >> rooms[i][j];
      total += rooms[i][j];
    }
  }
  cout << total - dp(0, 0, 0) << '\n';
}
