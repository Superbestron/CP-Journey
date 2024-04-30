#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;

void solve() {
  cin >> n;
  vi a(n), b;
  int ans = 0, to_cover = 0;
  for (int &i : a) {
    cin >> i;
    if (i == 0) ans++;
    if (b.empty()) b.push_back(i);
    else {
      if (i == 2) {
        if (b.back() == 1) b.back() = 2;
        else if (b.back() == 0) b.push_back(i);
      } else if (i == 1) {
        if (b.back() == 0) b.push_back(i);
      } else {
        b.push_back(i);
      }
    }
  }
  for (int i : b) {
    if (i != 0) ans++;
    if (i == 0) {
      if (to_cover == -1) {
        ans--;
        to_cover = 0;
      } else if (to_cover == 0) {
        to_cover = 1;
      }
    } else if (i == 1) {
      if (to_cover == 1) {
        ans--;
        to_cover = 0;
      } else if (to_cover == 0) {
        to_cover = -1; // cover forward
      }
    } else {
      if (to_cover == 1) {
        ans--;
      }
      to_cover = -1;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
//  cin >> t;
//  while (t--) {
    solve();
//  }
}
