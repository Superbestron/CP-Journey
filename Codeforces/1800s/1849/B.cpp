#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(n);
  vii b;
  for (int &i : a) cin >> i;
  for (int i = 0; i < n; i++) {
    b.emplace_back(a[i] % k, i + 1);
  }
  auto comp = [](const ii &x, const ii &y) {
    if (x.first == 0 && y.first == 0) return x.second < y.second;
    if (x.first == 0) return true;
    if (y.first == 0) return false;
    if (x.first == y.first) return x.second < y.second;
    return x.first > y.first;
  };
  sort(b.begin(), b.end(), comp);
  for (auto &[x, y] : b) cout << y << ' ';
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
