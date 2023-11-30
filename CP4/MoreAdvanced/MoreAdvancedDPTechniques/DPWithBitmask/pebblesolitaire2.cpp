#include <bits/stdc++.h>
using namespace std;

char c;
int n, memo[1 << 23];

int dp(int mask) {
  int &ans = memo[mask];
  if (ans != -1) return ans;
  ans = __builtin_popcount(mask);
  for (int i = 0; i < 22; i++) {
    if (mask & (1 << i) && mask & (1 << (i + 1))) {
      int m = mask;
      if (i != 0 && (mask & (1 << (i - 1))) == 0) {
        m &= ~(1 << i);
        m &= ~(1 << (i + 1));
        m |= (1 << (i - 1));
        ans = min(ans, dp(m));
      }
      m = mask;
      if (i != 21 && (mask & (1 << (i + 2))) == 0) {
        m &= ~(1 << i);
        m &= ~(1 << (i + 1));
        m |= (1 << (i + 2));
        ans = min(ans, dp(m));
      }
    }
  }
  return ans;
}

int main() {
  cin >> n;
  while (n--) {
    memset(memo, -1, sizeof memo);
    int bm = 0;
    for (int i = 0; i < 23; i++) {
      cin >> c;
      if (c == 'o') bm |= (1 << i);
    }
    cout << dp(bm) << '\n';
  }
}
