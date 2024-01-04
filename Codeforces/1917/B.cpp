#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;
string s;

void solve() {
  cin >> n >> s;
  unordered_set<char> st;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    char c = s[i];
    st.insert(c);
    ans += st.size();
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
