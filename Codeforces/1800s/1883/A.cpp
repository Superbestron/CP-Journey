#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  string s;
  cin >> t;
  while (t--) {
    cin >> s;
    char prev = '1';
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '0') s[i] = ':';
      ans += abs(s[i] - prev);
      ans++;
      prev = s[i];
    }
    cout << ans << '\n';
  }
}