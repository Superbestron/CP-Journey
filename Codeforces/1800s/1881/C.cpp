#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<string> v(n);
    for (auto& s : v) cin >> s;
    // outer square
    int cost = 0;
    for (int i = 0; i < n / 2; i++) {
      for (int j = i; j < n - i - 1; j++) {
        char first = v[i][j];
        char second = v[j][n - i - 1];
        char third = v[n - i - 1][n - 1 - j];
        char fourth = v[n - 1 - j][i];
        char maxi = max(first, max(second, max(third, fourth)));
        cost += (maxi - first)  + (maxi - second) + (maxi - third) + (maxi - fourth);
      }
    }
    cout << cost << '\n';
  }
}