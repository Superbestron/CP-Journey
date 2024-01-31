#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;

int t;
string s;

void solve() {
  cin >> s;
  int zero_count = 0, one_count = 0;
  for (char i : s) {
    if (i == '0') zero_count++;
    else one_count++;
  }
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '0') {
      if (one_count == 0) {
        cout << s.size() - i << '\n';
        return;
      }
      one_count--;
    } else {
      if (zero_count == 0) {
        cout << s.size() - i << '\n';
        return;
      }
      zero_count--;
    }
  }
  cout << 0 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
