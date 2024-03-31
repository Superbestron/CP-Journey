#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

char query(int a, int b, int c, int d) {
  char ch;
  cout << "? " << a << ' ' << b << ' ' << c <<  ' ' << d << endl;
  cin >> ch;
  return ch;
}

void solve() {
  cin >> n;
  vi v;
  // find max
  int mx = 0, mx_or = 0;
  for (int i = 1; i < n; i++) {
    char c = query(i, i, mx, mx);
    if (c == '>') mx = i;
  }
  // find max or
  v.push_back(0);
  for (int i = 1; i < n; i++) {
    char c = query(i, mx, mx_or, mx);
    if (c == '>') {
      v.clear();
      v.push_back(i);
      mx_or = i;
    } else if (c == '=') v.push_back(i);
  }
  // find min
  int mn = v[0];
  for (int i = 1; i < v.size(); i++) {
    char c = query(v[i], v[i], mn, mn);
    if (c == '<') mn = v[i];
  }
  cout << "! " << mn << ' ' << mx << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
