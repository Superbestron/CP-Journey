#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
const int MAX_N = 10000;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
int EulerPhi[MAX_N + 10];

void sieve(ll upperbound) { // range = [0..upperbound]
  sieve_size = upperbound + 1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = false; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i)
    if (bs[i]) {
// cross out multiples of i starting from i*i
      for (ll j = i * i; j < sieve_size; j += i) bs[j] = false;
      p.push_back(i); // add prime i to the list
    }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 1; i <= MAX_N; i++) EulerPhi[i] = i;
  for (int i = 2; i <= MAX_N; i++) {
    if (EulerPhi[i] == i) {
      for (int j = i; j <= MAX_N; j += i) EulerPhi[j] = (EulerPhi[j] / i) * (i - 1);
    }
  }
  for (int i = 2; i <= MAX_N; i++) EulerPhi[i] += EulerPhi[i - 1];
  int P, K, N;
  cin >> P;
  sieve(1000000);
  while (P--) {
    cin >> K >> N;
    cout << K << ' ' << EulerPhi[N] + 1 << '\n';
  }
}