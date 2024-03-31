#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, q;
string s;
const int p = 131;
const int M = 1e9 + 7;
vi P;

ll mod(ll a, int m) {                            // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, int p, int m) {                  // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                    // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

ll extEuclid(ll a, ll b, ll &x, ll &y) {    // pass x and y by ref
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {                                    // repeats until b == 0
    ll q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;                                      // returns gcd(a, b)
}

ll modInverse(ll b, int m) {                   // returns b^(-1) (mod m)
  ll x, y;
  ll d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

void prepareP(int n) {
  P.assign(n, 0);
  P[0] = 1;
  for (int i = 1; i < n; i++) {
    P[i] = ((ll) P[i - 1] * p) % M;
  }
}

vi computeRollingHash1(string &T) {
  vi h(n, 0);
  for (int i = 0; i < n; i++) {
    if (i != 0) h[i] = h[i - 1];
    h[i] = (h[i] + (ll) T[i] * P[i] % M) % M;
  }
  return h;
}

vi computeRollingHash2(string &T) {
  vi h(n, 0);
  for (int i = 0; i < n; i++) {
    if (i != 0) h[i] = h[i - 1];
    h[i] = (h[i] + (ll) T[i] * P[i] % M) % M;
  }
  return h;
}

int hash_fast(int L, int R, vi &h) {                    // O(1) hash of any substr
  if (L == 0) return h[R];                       // h is the prefix hashes
  int ans = ((h[R] - h[L - 1]) % M + M) % M;           // compute differences
  ans = ((ll) ans * modInverse(P[L], M)) % M;   // remove P[L]^-1 (mod M)
  return ans;
}

void solve() {
  cin >> n >> q >> s;
  vector<vi> prefsum(26, vi(n + 1));
  vector<vi> pref(26, vi(n + 2));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 26; j++) {
      prefsum[j][i + 1] += (s[i] - 'a' == j) + prefsum[j][i];
      pref[j][i + 2] += (s[i] - 'a' == j) + pref[j][i];
    }
  }
  prepareP(n);
  vi h1 = computeRollingHash1(s); // o(n)
  reverse(s.begin(), s.end());
  vi h2 = computeRollingHash2(s); // o(n)
  reverse(s.begin(), s.end());
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    vi &curr = prefsum[s[l] - 'a'];
    ll len = r - l + 1;
    if (curr[r + 1] - curr[l] == len) {
      cout << 0 << '\n';
      continue;
    }
    ll ans = len * (len + 1) / 2 - 1;
    char l_char = s[l];
    char next_char = s[l + 1];
    if (len & 1) {
      if (pref[l_char - 'a'][r + 2] - pref[l_char - 'a'][l] == (len + 1) / 2 &&
          pref[next_char - 'a'][r + 1] - pref[next_char - 'a'][l + 1] == len / 2) {
        ll new_len = len / 2;
        cout << (new_len) * (new_len + 1) << '\n';
        continue;
      }
      int mid = (l + r) / 2;
      int hash1 = hash_fast(l, mid - 1, h1);
      int hash2 = hash_fast(n - 1 - r, n - 1 - (mid + 1), h2);
      if (hash1 == hash2) ans -= len;
    } else {
      if (pref[l_char - 'a'][r + 1] - pref[l_char - 'a'][l] == len / 2 &&
          pref[next_char - 'a'][r + 2] - pref[next_char - 'a'][l + 1] == len / 2) {
        ll new_len = len / 2;
        cout << (new_len) * (new_len + 1) << '\n';
        continue;
      }
      int mid = (l + r) / 2;
      int hash1 = hash_fast(l, mid, h1);
      int hash2 = hash_fast(n - 1 - r, n - 1 - (mid + 1), h2);
      if (hash1 == hash2) ans -= len;
    }
    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
