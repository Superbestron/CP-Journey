#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, c1, c2, c3, c4;
const int MAX_N = 10000010;
const int p = 998244353;
ll fact[MAX_N];

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

ll inv(ll a) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}

ll C(int n, int k) {                             // O(log p)
  if (n < k) return 0;                           // clearly
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n - k])) % p;
}

ll modMultiply(ll a, ll b, ll c) {
  ll x = 0, y = a % c;
  while (b) {
    if (b & 1) x = (x + y) % c;
    y = (y * 2) % c;
    b >>= 1;
  }
  return x % c;
}

void solve() {
  cin >> c1 >> c2 >> c3 >> c4;
  if (abs(c1 - c2) > 1) {
    cout << 0 << '\n';
    return;
  }
  if (c1 == c2 && c1 == 0) {
    if (c3 != 0 && c4 != 0) cout << 0 << '\n';
    else cout << 1 << '\n';
    return;
  }
  int p3, p4;
  if (c1 > c2) {
    p4 = p3 = c1;
    int ans1 = C(c4 + p4 - 1, p4 - 1);
    int ans2 = C(c3 + p3 - 1, p3 - 1);
    int final = modMultiply(ans1, ans2, p);
    cout << final << '\n';
  } else if (c1 < c2) {
    p4 = p3 = c2;
    int ans1 = C(c4 + p4 - 1, p4 - 1);
    int ans2 = C(c3 + p3 - 1, p3 - 1);
    int final = modMultiply(ans1, ans2, p);
    cout << final << '\n';
  } else {
    p4 = c1 + 1; p3 = c1;
    int ans1 = C(c4 + p4 - 1, p4 - 1);
    int ans2 = C(c3 + p3 - 1, p3 - 1);
    int final1 = modMultiply(ans1, ans2, p);
    p4 = c1; p3 = c1 + 1;
    int ans3 = C(c4 + p4 - 1, p4 - 1);
    int ans4 = C(c3 + p3 - 1, p3 - 1);
    int final2 = modMultiply(ans3, ans4, p);
    cout << mod(final1 + final2, p) << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    fact[i] = (fact[i - 1] * i) % p;                  // fact[i] in [0..p-1]
  while (t--) {
    solve();
  }
}
