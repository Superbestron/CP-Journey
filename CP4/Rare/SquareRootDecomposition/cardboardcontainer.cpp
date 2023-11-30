#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int V; cin >> V;
  int srt = sqrt(V), ans = 1e9;
  for (int i = 1; i <= srt; i++) {
    for (int j = 1; j <= srt; j++) {
      int prod = i * j;
      if (V % prod) continue;
      int side = V / prod;
      ans = min(ans, 2 * prod + 2 * i * side + 2 * j * side);
    }
  }
  cout << ans << '\n';
}
