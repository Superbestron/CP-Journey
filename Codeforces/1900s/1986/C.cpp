#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;
string s, c;

inline void solve() {
  cin >> n >> m >> s;
  vi p(m), mx(n, 1e9);
  for (int &i : p) cin >> i;
  set<int> st;
  for (int &i : p) st.insert(i);
  cin >> c;
  sort(c.begin(), c.end());
  int cnt = 0;
  for (const int &i : st) {
    s[i - 1] = c[cnt];
    cnt++;
  }
  cout << s << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
}
