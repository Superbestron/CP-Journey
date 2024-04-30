#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int t, r1, c1, r2, c2;
string s;

inline void solve() {
  cout << "5 1 5 6" << endl;
  while (cin >> s && s != "GAME") {
    cin >> r1 >> c1 >> r2 >> c2;
    r2 = min(r2, 4);
    r1 = 5 - r1;
    r2 = 5 - r2;
    c1 = 7 - c1;
    c2 = 7 - c2;
    if (r1 > r2) swap(r1, r2);
    if (c1 > c2) swap(c1, c2);
    cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
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
