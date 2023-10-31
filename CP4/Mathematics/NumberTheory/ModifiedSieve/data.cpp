//#include <bits/stdc++.h>
//#define LSOne(S) S & (-S)
//using namespace std;
//typedef long long ll;
//typedef vector<ll> vll;
//
//ll sieve_size;
//bitset<14010> bs; // 10^7 is the rough limit
//vll p; // compact list of primes
//vector<int> v;
//vector<unordered_set<int>> diffPrimeFactors;
//vector<vector<int>> memo;
//unordered_set<int> s;
//int N;
//
//inline void intersect(unordered_set<int>& a, unordered_set<int>& b) {
//  for (int i : b) a.insert(i);
//}
//
//void primeFactors(int N) { // pre-condition, N >= 1
//  unordered_set<int>& factors = diffPrimeFactors[N];
//  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i) {
//    if (N % p[i] == 0) factors.insert(p[i]);
//    while (N % p[i] == 0) { // found a prime for N
//      N /= p[i]; // remove it from N
//    }
//  }
//  if (N != 1) factors.insert(N); // remaining N is a prime
//}
//
//void sieve(ll upperbound) { // range = [0..upperbound]
//  sieve_size = upperbound + 1; // to include upperbound
//  bs.set(); // all 1s
//  bs[0] = bs[1] = false; // except index 0+1
//  for (ll i = 2; i < sieve_size; ++i)
//    if (bs[i]) {
//// cross out multiples of i starting from i*i
//      for (ll j = i * i; j < sieve_size; j += i) bs[j] = false;
//      p.push_back(i); // add prime i to the list
//    }
//}
//
//int dp(int idx, int mask) {
//  if (idx == N) return s.size();
//  int& ans = memo[idx][mask];
//  if (ans != -1) return ans;
//  int m = mask;
//
//}
//
//int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
//  cin >> N;
//  memo.assign(N, vector<int>(1 << N, -1));
//  sieve(14000);
//  v.assign(N, 0);
//  diffPrimeFactors.assign(N + 1, unordered_set<int>());
//  for (int i = 2; i <= N; i++) primeFactors(i);
//  for (int &i : v) cin >> i;
//  cout << dp(0, (1 << N) - 1);
//}