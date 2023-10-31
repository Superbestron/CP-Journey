#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, N;
  cin >> T;
  while (T--) {
    cin >> N;
    if (N == 1) cout << "IMPOSSIBLE\n";
    else if (N & 1) {
      cout << N << " = " << N / 2 << " + " << N / 2 + 1 << '\n';
    } else {
      bool found = false;
      for (int i = 3; i < 31622; i++) {
        int prod = N - (i - 1) * i / 2;
        if (prod < i) break;
        if (prod % i == 0) {
          int base = prod / i;
          found = true;
          cout << N << " = ";
          bool first = true;
          for (int j = 0; j < i; j++) {
            if (first) first = false;
            else cout << " + ";
            cout << base + j;
          }
          cout << '\n';
          break;
        }
      }
      if (!found) cout << "IMPOSSIBLE\n";
    }
  }
}