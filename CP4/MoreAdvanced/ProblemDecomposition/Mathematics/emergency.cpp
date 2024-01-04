#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Almost got baited by SSSP, luckily I saw the bounds

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, K;
  cin >> n >> K;
  n--;
  if (n < 2 * K) cout << n << '\n';
  else cout << K + 1 + n % K << '\n';
}
