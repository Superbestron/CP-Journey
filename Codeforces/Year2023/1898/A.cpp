#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, k;
string s;

void solve() {
  cin >> n >> k >> s;
  int cnt_A = 0, cnt_B = 0;
  for (char c : s) {
    if (c == 'B') cnt_B++;
  }
  if (k == cnt_B) {
    cout << 0 << '\n';
    return;
  }
  else {
    int diff = abs(cnt_B - k);
    if (cnt_B < k) {
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'A') cnt_A++;
        if (cnt_A == diff) {
          cout << 1 << '\n' << i + 1 << " B" << '\n';
          return;
        }
      }
    } else {
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'B') cnt_B--;
        if (cnt_B == k) {
          cout <<  1 << '\n' << i + 1 << " A" << '\n';
          return;
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
