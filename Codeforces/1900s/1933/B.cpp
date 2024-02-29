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
  vi a(n);
  vi b(2);
  int sum = 0;
  for (int &i : a) {
    cin >> i;
    sum = (sum + i) % 3;
    if (i % 3 == 1) b[0]++;
    else if (i % 3 == 2) b[1]++;
  }
  if (sum == 0) cout << 0 << '\n';
  else if (sum == 1) {
    if (b[0] > 0) cout << 1 << '\n';
    else cout << 2 << '\n';
  } else cout << 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
