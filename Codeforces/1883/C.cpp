#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, k, num;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    int maxi = 1;
    int mod = 0, mod2 = 0, mod1 = 0;
    for (int i = 0; i < n; i++) {
      cin >> num;
      if (num % k == 0) mod++;
      if (k == 4 && num % 2 == 0) mod2++;
      if (num % k == 1) mod1++;
      maxi = max(maxi, num % k);
    }
    if (mod || (k == 4 && mod2 >= 2)) cout << 0 << '\n';
    else {
      if (k == 4) {
        if (mod2 == 1 && mod1) cout << 1 << '\n';
        else cout << min(k - maxi, 2) << '\n';
      } else {
        cout << k - maxi << '\n';
      }
    }
    int x = 5;
  }
}