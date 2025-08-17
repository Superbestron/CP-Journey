#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

inline void solve() {
  cin >> n >> m;
  vector<vi> AL(n, vi(m)), ALB(n, vi(m));
  map<int, set<int>> r_mp, c_mp;
  for (auto &row : AL) {
    int least = 1e9;
    set<int> st;
    for (int &i : row) {
      cin >> i;
      least = min(least, i);
      st.insert(i);
    }
    r_mp[least] = st;
  }
  for (int j = 0; j < m; j++) {
    int least = 1e9;
    set<int> st;
    for (int i = 0; i < n; i++) {
      least = min(least, AL[i][j]);
      st.insert(AL[i][j]);
    }
    c_mp[least] = st;
  }
  bool can = true;
  for (auto &row : ALB) {
    int least = 1e9;
    set<int> st;
    for (int &i : row) {
      cin >> i;
      least = min(least, i);
      st.insert(i);
    }
    if (st != r_mp[least]) {
      can = false;
    }
  }
  for (int j = 0; j < m; j++) {
    int least = 1e9;
    set<int> st;
    for (int i = 0; i < n; i++) {
      least = min(least, ALB[i][j]);
      st.insert(ALB[i][j]);
    }
    if (st != c_mp[least]) {
      can = false;
      break;
    }
  }
  if (can) cout << "YES\n";
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
