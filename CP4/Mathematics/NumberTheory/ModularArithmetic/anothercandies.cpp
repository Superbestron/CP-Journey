#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll T, N, v;
  cin >> T;
  while (T--) {
    cin >> N;
    ll sum = 0;
    for (int i = 0; i < N; i++) {
      cin >> v;
      sum = (sum + (v % N)) % N;
    }
    if (sum) cout << "NO\n";
    else cout << "YES\n";
  }
}