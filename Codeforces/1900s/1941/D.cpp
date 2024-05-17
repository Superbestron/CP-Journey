#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, x, r;
char c;

inline void solve() {
  cin >> n >> m >> x;
  x--;
  unordered_set<int> s;
  s.insert(x);
  for (int i = 0; i < m; i++) {
    cin >> r >> c;
    unordered_set<int> new_s;
    for (int idx : s) {
      if (c == '0') {
        new_s.insert((idx + r) % n);
      } else if (c == '1') {
        new_s.insert((idx - r + n) % n);
      } else {
        new_s.insert((idx + r) % n);
        new_s.insert((idx - r + n) % n);
      }
    }
    s = new_s;
  }
  cout << s.size() << '\n';
  vi a;
  for (int idx : s) a.push_back(idx);
  sort(a.begin(), a.end());
  for (int i : a) cout << i + 1 << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
