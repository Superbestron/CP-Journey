#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;
string s;

inline void solve() {
  cin >> n >> s;
  int idx = 0;
  int max_r = n - 1;
  while (max_r >= 0 && s[max_r] == 'A') {
    max_r--;
    s.pop_back();
  }
  while (idx < s.size() && s[idx] == 'B') {
    idx++;
  }
  bool found = false;
  for (int i = idx; i < s.size(); i++) {
    if (s[i] == 'B') found = true;
  }

  if (found) cout << s.size() - idx - 1 << '\n';
  else cout << 0 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
