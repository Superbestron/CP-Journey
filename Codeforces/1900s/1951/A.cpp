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
  cin >> n >> s;
  int one_cnt = 0;
  bool beside = false;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') one_cnt++;
    if (i > 0 && s[i] == s[i - 1] && s[i] == '1') beside = true;
  }
  if (one_cnt == 2 && beside) cout << "NO\n";
  else if (one_cnt % 2 == 0) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
