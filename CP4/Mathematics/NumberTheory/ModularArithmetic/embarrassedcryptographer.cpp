#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int sieve_size;
bitset<1000010> bs; // 10^7 is the rough limit
vi p; // compact list of primes

void sieve(int upperbound) { // range = [0..upperbound]
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
  sieve(1000000);
  string K;
  int L;
  while (cin >> K >> L) {
    if (K == "0" && L == 0) break;
    bool can = true;
    reverse(K.begin(), K.end());
    while (K.size() % 3 != 0) K += '0';
    for (int i = 0; i < p.size() && p[i] < L; i++) {
      int val = 0;
      for (int j = K.size() - 1; j >= 0; j -= 3) {
        val *= 10;
        val += K[j] - '0';
        val *= 10;
        val += K[j - 1] - '0';
        val *= 10;
        val += K[j - 2] - '0';
        if (val >= p[i]) val %= p[i];
      }
      if (val == 0) {
        cout << "BAD " << p[i] << '\n';
        can = false;
        break;
      }
    }
    if (can) cout << "GOOD " << '\n';
  }
}
