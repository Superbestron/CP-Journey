#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int tc, n, m;
string s1, s2;

void solve() {
  cin >> n >> m >> s1 >> s2;
  int ans = 0;
  for (int i = 0, j = 0; i < n; i++) {
    while (j < m) {
      if (s1[i] == s2[j++]) goto done;
    }
    break;
    done:
    ans++;
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> tc;
  while (tc--) {
    solve();
  }
}
