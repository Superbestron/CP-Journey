#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<14010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
vector<int> v;
vector<vector<int>> memo;
vector<int> numDiffPF;

void fill_numDiffPF(int _upperbound) {
  numDiffPF.assign(_upperbound, 0);
  for (int i = 2; i <= _upperbound; i++) {
    if (numDiffPF[i] == 0) {  // i is prime
      for (int j = i; j <= _upperbound; j += i) {
        numDiffPF[j]++;  // j is divisible by prime i
      }
    }
  }
}

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

int dp(int idx, int mask) {
  if (mask == 0) return 0;
  int& ans = memo[idx][mask];
  if (ans != -1) return ans;
  for (int subset = mask; subset; subset = (mask & (subset - 1))) {
    int curr = subset, sum = 0;
    while (curr) {
      int two_pow = LSOne(curr);
      int j = __builtin_ctz(two_pow);
      sum += v[j];
      curr -= two_pow;
    }
    ans = max(ans, numDiffPF[sum] + dp(idx + 1, mask - subset));
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  memo.assign(N, vector<int>(1 << N, -1));
  sieve(14000);
  fill_numDiffPF(14000);
  v.assign(N, 0);
  for (int &i : v) cin >> i;
  cout << dp(0, (1 << N) - 1);
}