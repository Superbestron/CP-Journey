#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vll;

ll sieve_size;
bitset<100010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
unordered_map<int, int> pf;

ll fexp(ll b, ll p) {
  if (p == 0)return 1;
  if (p == 1)return b;
  if (p & 1) {
    return fexp(b, p >> 1) * fexp(b, p >> 1) * b;
  } else {
    return fexp(b, p >> 1) * fexp(b, p >> 1);
  }
}

unordered_map<int, int> primeFactors(ll N) { // pre-condition, N >= 1
  unordered_map<int, int> m;
  for (ll i = 0; i < (int) p.size() && p[i] * p[i] <= N; i++) {
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      pf[p[i]]++;
      m[p[i]]++;
    }
  }
  if (N > 1) {
    m[N]++;
    pf[N]++;
  }
  return m;
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, V, ans = 0, sum = 1;
  sieve(100000);
  cin >> N;
  vector<unordered_map<int, int>> v;
  for (int i = 0; i < N; i++) {
    cin >> V;
    v.push_back(std::move(primeFactors(V)));
  }
  for (auto& [num, cnt] : pf) {
    sum *= fexp(num, cnt / N);
    for (auto& factors : v) {
      if (factors[num] < cnt / N) {
        ans += cnt / N - factors[num];
      }
    }
  }
  cout << sum << ' ' << ans;
}