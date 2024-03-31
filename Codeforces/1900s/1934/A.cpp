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
  vi a;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  int x1 = a.back(); a.pop_back();
  int x2 = a.back(); a.pop_back();
  sort(a.begin(), a.end(), greater<>());
  int x3 = a.back(); a.pop_back();
  int x4 = a.back(); a.pop_back();
  cout << (x1 - x4) + (x1 - x3) + (x2 - x4) + (x2 - x3) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
