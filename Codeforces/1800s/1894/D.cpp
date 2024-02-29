#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vi a(n), b(m), c(n + m);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  sort(b.begin(), b.end(), greater<>());
  merge(a.begin(), a.end(), b.begin(), b.end(), c.begin(), greater<>());
  for (int i : c) cout << i << ' ';
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
