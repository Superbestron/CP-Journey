#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> v(n - 1);
    int sum = 0;
    for (int &i : v) {
      cin >> i;
      sum += i;
    }
    cout << -sum << '\n';
  }
}