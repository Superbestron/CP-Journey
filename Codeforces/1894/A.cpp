#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;
string s;

void solve() {
  cin >> n >> s;
  bool isA = s.back() == 'A';
  for (int i = 1; i <= 20; i++) {
    int a_ctr = 0, b_ctr = 0, a_set_ctr = 0, b_set_ctr = 0;
    for (int j = 0; j < n; j++) {
      if (s[j] == 'A') a_ctr++;
      else b_ctr++;
      if (a_ctr == i || b_ctr == i) {
        if (a_ctr == i) a_set_ctr++;
        else b_set_ctr++;
        a_ctr = 0; b_ctr = 0;
      }
    }
    if (a_ctr == 0 && b_ctr == 0) {
      if (isA && a_set_ctr > b_set_ctr) {
        cout << "A\n";
        return;
      }
      if (!isA && a_set_ctr < b_set_ctr) {
        cout << "B\n";
        return;
      }
    }
  }
  cout << "?\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}