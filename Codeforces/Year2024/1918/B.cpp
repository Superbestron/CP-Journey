#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  vii v;
  for (int i = 0; i < n; i++) {
    v.emplace_back(a[i], b[i]);
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n; i++) {
    cout << get<0>(v[i]) << ' ';
  }
  cout << '\n';
  for (int i = 0; i < n; i++) {
    cout << get<1>(v[i]) << ' ';
  }
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
