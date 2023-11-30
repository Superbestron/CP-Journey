#include <bits/stdc++.h>
using namespace std;

int main() {
  int m, n;
  double X, Y, a, b;
  cin >> m;
  while (m--) {
    cin >> X >> Y >> n;
    bool light = false;
    while (n--) {
      cin >> a >> b;
      if (hypot(X - a, Y - b) <= 8) light = true;
    }
    if (light) cout << "light a candle\n";
    else cout << "curse the darkness\n";
  }
}
