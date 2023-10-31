#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vll;
const int MAX_N = 2e6;

ll sieve_size;
bitset<1000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
int numDiffPFarr[MAX_N + 10] = {0}; // e.g., MAX_N = 10^7
int numDivArr[MAX_N + 10]; // e.g., MAX_N = 10^7

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

int numDiv(ll N) {
  int ans = 1;                                   // start from ans = 1
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    int power = 0;                               // count the power
    while (N % p[i] == 0) {
      N /= p[i];
      ++power;
    }
    ans *= power + 1;                              // follow the formula
  }
  return (N != 1) ? 2 * ans : ans;                 // last factor = N^1
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int Q, N;
  sieve(1000000);
  for (int i = 2; i <= MAX_N; ++i)
    if (numDiffPFarr[i] == 0) // i is a prime number
      for (int j = i; j <= MAX_N; j += i)
        ++numDiffPFarr[j]; // j is a multiple of i
  memset(numDivArr, 0, sizeof numDivArr);
  for (int i = 1; i <= MAX_N; ++i) {
    for (ll j = i; j <= MAX_N; j += i) {
      numDivArr[j]++;
    }
  }
  cin >> Q;
  while (Q--) {
    cin >> N;
    cout << numDivArr[N] - numDiffPFarr[N] << '\n';
  }
}