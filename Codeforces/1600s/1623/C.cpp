#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> h;
int t, n;
inline bool can(int x) {
  vector<int> v = h;
  for (int i = n - 1; i >= 2; i--) {
    if (v[i] < x) return false;
    int d = min(h[i], (v[i] - x)) / 3;
    v[i - 1] += d;
    v[i - 2] += (d << 1);
  }
  return v[0] >= x && v[1] >= x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n;
    int lo = 0, hi = 0;
    h.assign(n, 0);
    for (int &i : h) {
      cin >> i;
      hi = max(hi, i);
    }
    while (hi > lo) {
      int mid = (lo + hi + 1) / 2;
      can(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo << '\n';
  }
}