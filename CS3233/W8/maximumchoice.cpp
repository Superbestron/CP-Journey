#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

ll n, b;

void solve() {
  cin >> n >> b;
  cout << (ll) ceil(log(n + 1) / log(b + 1)) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
