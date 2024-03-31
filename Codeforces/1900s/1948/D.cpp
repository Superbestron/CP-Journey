#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;

void solve() {
  cin >> s;
  int n = s.size();
  int ans = 0;
  // try all halves
  for (int i = n / 2; i > 0; i--) {
    int len = 0;
    for (int j = 0; j + i < n; j++) {
      if (s[j] == '?' || s[j + i] == '?') len++;
      else if (s[j] == s[j + i]) len++;
      else len = 0;
      if (len == i) {
        ans = max(ans, len * 2);
        break;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
