#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

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

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int c; cin >> c;
  string s;
  sieve(10000000);
  while (c--) {
    cin >> s;
    unordered_set<int> st;
    int len = s.size();
    int arr[len];
    for (int i = 1; i < (1 << len); i++) {
      string selected_chars;
      int bm = i;
      while (bm) {
        int two_pow = LSOne(bm);
        int idx = __builtin_ctz(bm);
        selected_chars += s[idx];
        bm -= two_pow;
      }
      int chars_len = selected_chars.size();
      for (int j = 0; j < chars_len; j++) arr[j] = j;
      do {
        string num_str;
        for (int k = 0; k < chars_len; k++) num_str += selected_chars[arr[k]];
        if (num_str[0] == '0') continue;
        int num = stoi(num_str);
        if (isPrime(num)) st.insert(num);
      } while (next_permutation(arr, arr + chars_len));
    }
    cout << st.size() << '\n';
  }
}
