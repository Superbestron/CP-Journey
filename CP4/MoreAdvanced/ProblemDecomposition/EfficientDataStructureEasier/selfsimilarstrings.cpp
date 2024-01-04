#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  unordered_map<string_view, int> m;
  while (cin >> s) {
    string_view str(s);
    for (int len = s.size() - 1; len >= 0; len--) {
      m.clear();
      for (int i = 0; i <= s.size() - len; i++) {
        string_view sub(str.substr(i, len));
        m[sub]++;
      }
      bool can = true;
      for (auto &[t, cnt] : m) {
        if (cnt < 2) {
          can = false;
          break;
        }
      }
      if (can) {
        cout << len << '\n';
        break;
      }
    }
  }
}
