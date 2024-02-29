#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n;

void solve() {
  cin >> n;
  if (n <= 28) {
    cout << "aa";
    cout << (char) (n - 2 + 'a' - 1) << '\n';
  } else if (n <= 53) {
    cout << "a";
    cout << (char) (n - 27 + 'a' - 1);
    cout << "z" << '\n';
  } else {
    cout << (char) (n - 52 + 'a' - 1);
    cout << "zz\n";
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
