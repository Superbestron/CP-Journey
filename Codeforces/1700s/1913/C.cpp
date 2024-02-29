#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;

int m, q, v;

vi get_bit_rep(int n) {
  vi bit(32);
  for (int i = 0; i < 32; i++) {
    if ((1 << i) & n) bit[i]++;
  }
  return bit;
}

void solve() {
  cin >> m;
  vi freq(32);
  for (int i = 0; i < m; i++) {
    cin >> q >> v;
    if (q == 1) {
      freq[v]++;
    } else {
      vi bit_rep = get_bit_rep(v);
      vi temp = freq;
      bool can = true;
      for (int bit = 31; bit >= 0; bit--) {
        // need borrow lower bits to make up
        if (bit_rep[bit] > temp[bit]) {
          if (bit == 0) {
            can = false;
          } else {
            // 2 smaller bits to make up 1 bit
            int need = bit_rep[bit] - temp[bit];
            temp[bit - 1] -= need * 2;
          }
        }
      }
      if (can) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
