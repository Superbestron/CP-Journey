#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  int n1 = n, n2 = n;
  int x15 = n / 15;
  n -= x15 * 15;
  int x10 = n / 10;
  n -= x10 * 10;
  int x6 = n / 6;
  n -= x6 * 6;
  int x3 = n / 3;
  n -= x3 * 3;
  int ans1 = 1e9 + 5, ans2 = 1e9 + 5, ans3 = 1e9 + 5;
  ans1 = x15 + x10 + x6 + x3 + n;

  if (n1 - 20 >= 0) {
    n1 -= 20;
    int x15 = n1 / 15;
    n1 -= x15 * 15;
    int x10 = n1 / 10;
    n1 -= x10 * 10;
    int x6 = n1 / 6;
    n1 -= x6 * 6;
    int x3 = n1 / 3;
    n1 -= x3 * 3;
    ans2 = 2 + x15 + x10 + x6 + x3 + n1;
  }
  if (n2 - 12 >= 0) {
    n2 -= 12;
    int x15 = n2 / 15;
    n2 -= x15 * 15;
    int x10 = n2 / 10;
    n2 -= x10 * 10;
    int x6 = n2 / 6;
    n2 -= x6 * 6;
    int x3 = n2 / 3;
    n2 -= x3 * 3;
    ans3 = 2 + x15 + x10 + x6 + x3 + n2;
  }
  cout << min(min(ans2, ans3), ans1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
