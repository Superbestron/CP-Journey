#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b;
  while (cin >> a >> b && !(a == 0 || b == 0)) {
    cout << a / b << ' ' << a % b << " / " << b << '\n';
  }
}
