#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

void solve() {
  cin >> n >> m;
  cout << "? 1 1" << endl;
  int d1, d2, d3, d4; cin >> d1;
  int qx2, qy2, qx3, qy3, qx4, qy4, fx, fy;
  if (d1 == 0) {
    cout << "! 1 1" << endl;
    return;
  }
  // cut off
  if (d1 >= n) {
    qx2 = n;
    qy2 = d1 - (n - 1) + 1;
  } else {
    qx2 = d1 + 1;
    qy2 = 1;
  }
  cout << "? " << qx2 << ' ' << qy2 << endl;
  cin >> d2;
  // chance stone is further up in diagonal
  if (d2 <= 2 * (qx2 - 1) && d2 % 2 == 0) {
    d2 /= 2;
    qx3 = qx2 - d2;
    qy3 = qy2 + d2;
    cout << "? " << qx3 << ' ' << qy3 << endl;
    cin >> d3;
    if (d3 == 0) {
      cout << "! " << qx3 << ' ' << qy3 << endl;
      return;
    }
  }
  int mx = min(m - qy2, qx2 - 1);
  qx4 = qx2 - mx;
  qy4 = qy2 + mx;
  cout << "? " << qx4 << ' ' << qy4 << endl;
  cin >> d4;
  d4 /= 2;
  fx = qx4 + d4;
  fy = qy4 - d4;
  cout << "! " << fx << ' ' << fy << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
