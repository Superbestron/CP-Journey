#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, S, D, K;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cin >> S >> D >> K;
    int burgers = 2 * S, cheese = S;
    burgers += 2 * D, cheese += 2 * D;
    if (burgers >= K + 1 && cheese >= K) printf("Case #%d: %s\n", i, "YES");
    else printf("Case #%d: %s\n", i, "NO");
  }
}