#include <bits/stdc++.h>
using namespace std;

int sum_of_digits(int n) {
  int sum = 0;
  while (n) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, x, k;
  cin >> t;
  while (t--) {
    cin >> x >> k;
    for (int i = x; i <= 2e9; i++) {
      if (sum_of_digits(i) % k == 0) {
        cout << i << '\n';
        break;
      }
    }
  }
}