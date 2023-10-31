#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    vector<int> pos_zeros;
    for (int i = s.size() - 1; i >= 0; i--) {
      if (s[i] == '0') pos_zeros.push_back(s.size() - i - 1);
    }
    long long ctr = 0, ans = 0;
    for (; ctr < pos_zeros.size(); ctr++) {
      ans += pos_zeros[ctr] - ctr;
      cout << ans << ' ';
    }
    for (; ctr < s.size(); ctr++) cout << -1 << ' ';
    cout << '\n';
  }
}