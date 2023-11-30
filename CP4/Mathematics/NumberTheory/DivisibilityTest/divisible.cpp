#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, d, n;
  cin >> t;
  while (t--) {
    cin >> d >> n;
    vector<int> v(n);
    unordered_map<int, int> m;
    int sum = 0, ans = 0;
    m[0] = 1;
    for (int &i : v) {
      cin >> i;
      sum = (sum + i) % d;
      ans += m[sum];
      m[sum]++;
    }
    cout << ans << '\n';
  }
}