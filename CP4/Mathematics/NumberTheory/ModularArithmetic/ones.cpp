#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n) {
    if (n == 1) {
      cout << 1 << '\n';
      continue;
    }
    int curr = 10, ans = 1;
    n *= 9;
    while (curr != 1) {
      curr *= 10;
      curr %= n;
      ans++;
    }
    cout << ans << '\n';
  }
}