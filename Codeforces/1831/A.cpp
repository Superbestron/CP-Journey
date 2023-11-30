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
    vector<int> v(n), ans;
    for (int &i : v) {
      cin >> i;
      cout << n - i + 1 << ' ';
    }
    cout << '\n';
  }
}
