#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b, c, d, t = 1;
  while (cin >> a >> b >> c >> d) {
    cout << "Case " << t++ << ":\n";
    int e = a * d - b * c;
    cout << d / e << ' ' << -b / e << '\n';
    cout << -c / e << ' ' << a / e << '\n';
  }
}