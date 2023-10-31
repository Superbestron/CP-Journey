#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n; cin >> t;
  while (t--) {
    cin >> n;
    vector<int> x, y;
    bool put_x = true;
    while (n) {
      int digit = n % 10;
      if (digit % 2 == 0) {
        x.push_back(digit / 2);
        y.push_back(digit / 2);
      } else {
        if (put_x) {
          x.push_back(digit / 2 + 1);
          y.push_back(digit / 2);
          put_x = false;
        } else {
          x.push_back(digit / 2);
          y.push_back(digit / 2 + 1);
          put_x = true;
        }
      }
      n /= 10;
    }
    while (x.size() > 1 && x.back() == 0) x.pop_back();
    while (y.size() > 1 && y.back() == 0) y.pop_back();
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    for (int i : x) cout << i;
    cout << ' ';
    for (int i : y) cout << i;
    cout << '\n';
  }
}
