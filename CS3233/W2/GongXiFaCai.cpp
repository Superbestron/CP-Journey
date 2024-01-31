#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;

int t, n;
string s;

void solve() {
  cin >> s;
  unordered_map<char, int> m;
  for (char &c : s) {
    c = tolower(c);
    m[c]++;
  }
  int ans = 1e9;
  ans = min(ans, m['g'] / 2);
  ans = min(ans, m['o']);
  ans = min(ans, m['n']);
  ans = min(ans, m['x']);
  ans = min(ans, m['i'] / 2);
  ans = min(ans, m['f']);
  ans = min(ans, m['a'] / 2);
  ans = min(ans, m['c']);
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
