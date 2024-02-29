#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;

int t, h, w, xa, ya, xb, yb;

void solve() {
  cin >> h >> w >> xa >> ya >> xb >> yb;
  // trivial Draw
  int diff = xb - xa - 1;
  int diff2 = abs(yb - ya) - 1;
  if (xb <= xa) cout << "Draw\n";
  else if (diff % 2 == 0) {
    // Alice might win
    // check if Alice is left of bob
    if (abs(ya - yb) <= 1) cout << "Alice\n";
    else if (ya < yb) {
      if (diff / 2 - (w - yb) >= diff2) cout << "Alice\n";
      else {
        cout << "Draw\n";
      }
    }
    else {
      if (diff / 2 - (yb - 1) >= diff2) cout << "Alice\n";
      else {
        cout << "Draw\n";
      }
    }
  } else {
    // Bob might win
    if (ya > yb) {
      if (diff / 2 - (w - ya) >= diff2) cout << "Bob\n";
      else cout << "Draw\n";
    }
    else if (ya < yb) {
      if (diff / 2 - (ya - 1) >= diff2) cout << "Bob\n";
      else cout << "Draw\n";
    }
    else cout << "Bob\n";
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
