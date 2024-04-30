#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int n, m;

inline void solve() {
  cin >> n >> m;
  vector<vi> E_m(n, vi(26)), S_m(m, vi(26));
  vector<string> E;
  unordered_map<string, vi> mp;
  string s;
  for (int i = 0; i < n; i++) {
      cin >> s;
      string copy = s;
      sort(copy.begin(), copy.end());
      mp[copy].push_back(i);
      E.emplace_back(s);
  }
  for (int i = 0; i < m; i++) {
      cin >> s;
      cout << s << ' ';
      string copy = s;
      sort(copy.begin(), copy.end());
      vi arr = mp[copy];
      for (int j : arr) {
          if (E[j] == s) continue;
          cout << E[j] << ' ';
      }
      cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
