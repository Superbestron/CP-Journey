#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll tc, n, m;
  string s, t;
  cin >> tc;
  while (tc--) {
    cin >> n >> m >> s >> t;
    bool shas11 = false, shas00 = false;
    char prev = '9';
    for (char c : s) {
      if (c == '1') {
        if (c == prev) shas11 = true;
      } else {
        if (c == prev) shas00 = true;
      }
      prev = c;
    }
    bool thas11 = false, thas00 = false;
    prev = '9';
    for (char c : t) {
      if (c == '1') {
        if (c == prev) thas11 = true;
      } else {
        if (c == prev) thas00 = true;
      }
      prev = c;
    }
    if (!shas11 && !shas00) {
      cout << "YES\n";
    } else if (shas11 && shas00) {
      cout << "NO\n";
    } else {
      if (thas00 || thas11) {
        cout << "NO\n";
      } else {
        if (shas11) {
          if (t[0] == '0' && t.back() == '0') cout << "YES\n";
          else cout << "NO\n";
        } else {
          if (t[0] == '1' && t.back() == '1') cout << "YES\n";
          else cout << "NO\n";
        }
      }
    }
  }
}