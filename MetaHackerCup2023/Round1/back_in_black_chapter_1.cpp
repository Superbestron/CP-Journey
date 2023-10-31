#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, N, Q, x;
  cin >> T;
  string s;
  for (int t = 1; t <= T; t++) {
    cin >> N >> s >> Q;
    vector<bool> presses(N + 1);
    while (Q--) {
      cin >> x;
      presses[x] = !presses[x];
    }
    for (int i = 1; i <= N; i++) {
      if (presses[i]) {
        for (int j = i; j <= N; j += i) {
          s[j - 1] ^= 1;
        }
      }
    }
    int num_presses = 0;
    for (int i = 1; i <= N; i++) {
      if (s[i - 1] == '1') {
        num_presses++;
        for (int j = i; j <= N; j += i) {
          s[j - 1] ^= 1;
        }
      }
    }
    printf("Case #%d: %d\n", t, num_presses);
  }
}