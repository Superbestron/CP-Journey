#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int n;

void solve() {
  cin >> n;
  vi a(n), idx(n);
  for (int &i : a) cin >> i;
  for (int i = 0; i < n; i++) idx[i] = i;
  bool found = false;
  do {
    bool can = true;
    for (int i = 1; i < n; i++) {
      int left = a[idx[i - 1]];
      int right = a[idx[i]];
      if (gcd(left, right) == 1) can = false;
    }
    if (can) {
      found = true;
      for (int i = 0; i < n; i++) {
        cout << a[idx[i]] << ' ';
      }
      cout << '\n';
      break;
    }
  } while (next_permutation(idx.begin(), idx.end()));
  if (!found) cout << "Neibb\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
