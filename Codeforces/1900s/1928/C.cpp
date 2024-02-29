#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

int t, n, x;

vll getDivisors(ll n) {
  vll ans;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i) ans.push_back(i);
      else {
        ans.push_back(i);
        ans.push_back(n / i);
      }
    }
  }
  return ans;
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

void solve() {
  cin >> n >> x;
  unordered_set<int> s;
  // 1. if at start
  if (x == 1) {
    vll pf = getDivisors(n - 1);
    for (ll i : pf) {
      if (i % 2 != 0) continue;
      if ((i + 2) / 2 < x) continue;
      s.insert((i + 2) / 2);
    }
  } else {
    // 2. if in increasing seq
    vll pf = getDivisors(n - x);
    for (ll i : pf) {
      if (i % 2 != 0) continue;
      if ((i + 2) / 2 < x) continue;
      s.insert((i + 2) / 2);
    }
    // 3. if in decreasing seq
    pf = getDivisors(n + x - 2);
    for (ll i : pf) {
      if (i % 2 != 0) continue;
      if ((i + 2) / 2 < x) continue;
      s.insert((i + 2) / 2);
    }
  }


  cout << s.size() << '\n';
//  for (int i : s) cout <<i << ' ';
//  cout << '\n';
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  sieve(10000000);
  while (t--) {
    solve();
  }
}
