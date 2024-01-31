#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, k, m;
string s;

// 1. freq of each char >= k
// 2.

void solve() {
  cin >> n >> k >> m >> s;
  int sect = 0;
  string last;
  unordered_set<char> st;
  for (int i = 0; i < m; i++) {
    st.insert(s[i]);
    if (st.size() == k) {
      last += s[i];
      st.clear();
      sect++;
    }
  }
  if (sect >= n) cout << "YES\n";
  else {
    cout << "NO\n";
    char missing;
    for (char c = 'a'; c < 'a' + k; c++) {
      if (!st.count(c)) {
        missing = c;
        break;
      }
    }
    last += missing;
    for (int i = last.size(); i < n; i++) last += missing;
    cout << last << '\n';
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
