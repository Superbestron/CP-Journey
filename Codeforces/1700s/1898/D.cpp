#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  ll score = 0;
  int max_leftep = -1, min_rightep = 1e9;
  for (int i = 0; i < n; i++) {
    score += (abs(a[i] - b[i]));
    max_leftep = max(max_leftep, min(a[i], b[i]));
    min_rightep = min(min_rightep, max(a[i], b[i]));
  }
  if (max_leftep > min_rightep) score += 2 * (max_leftep - min_rightep);
  cout << score << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
