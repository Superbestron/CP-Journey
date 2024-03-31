#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;

// Editorial explains very poorly, let me explain it here
// Idea is that b1 ^ b2 = a1, b1 ^ b3 = a1 ^ a2, b1 ^ b4 = a1 ^ a2 ^ a3
// which leads into b1 = b1 ^ 0, b2 = b1 ^ a1, b3 = b1 ^ (a1 ^ a2), b4 = b1 ^ (a1 ^ a2 ^ a3)
// Since xor is a bitwise operation, we can analyse bit-by-bit
// We will now try to find the value of b1
// Notice that the ith bit of b1 and either be 1 or 0
// If ith bit of b1 is 0, the sum of ith bit from 0 to n - 1 must be equals to
// sum of ith bit from 0, a1, a1 ^ a2, a1 ^ a2 ^ a3 BECAUSE taking b2 = b1 ^ a1 as example,
// b2_i = 0 ^ a1_i = a1_i, so sum of left = sum of right
// IF the sum is not equal, then ith bit of b1 must be 1, and we are guaranteed that
// this is correct because there is always a solution
// Once we know the value of b1, we can calculate the rest of the bis

void solve() {
  cin >> n;
  vi a(n - 1), pref(1), target(20), actual(20);
  for (int &i : a) cin >> i;
  for (int i = 0; i < n - 1; i++) {
    pref.push_back(pref.back() ^ a[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 20; j++) {
      actual[j] += pref[i] & (1 << j);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 20; j++) {
      target[j] += i & (1 << j);
    }
  }
  int b1 = 0;
  for (int i = 0; i < 20; i++) {
    if (actual[i] != target[i]) b1 ^= 1 << i;
  }
  for (int i = 0; i < n; i++) cout << (b1 ^ pref[i]) << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
