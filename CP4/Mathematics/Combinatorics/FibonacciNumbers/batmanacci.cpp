#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

ll N, K;
vector<ll> fibo(1e5 + 1);

char recurse(ll n, ll k) {
  if (n == 1) return 'N';
  else if (n == 2) return 'A';
  ll first = fibo[n - 2];
  if (k <= first) return recurse(n - 2, k);
  else return recurse(n - 1, k - first);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  fibo[1] = 1;
  fibo[2] = 1;
  for (int i = 3; i <= 1e5; i++) {
    fibo[i] = fibo[i - 2] + fibo[i - 1];
    if (fibo[i] > 1e18) fibo[i] = 1e18 + 1;
  }
  cin >> N >> K;
  cout << recurse(N, K) << '\n';
}
