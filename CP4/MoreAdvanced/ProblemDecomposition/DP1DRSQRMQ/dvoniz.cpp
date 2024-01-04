#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, S;
  cin >> N >> S;
  vector<int> v(N);
  vector<ll> prefix(N + 1);
  for (int &i : v) cin >> i;
  prefix[0] = 0;
  for (int i = 0; i < N; i++) prefix[i + 1] = prefix[i] + v[i];
  for (int l = 0; l < N; l++) {
    // binary search for longest subseq length
    int lo = 0, hi = (N - l) / 2;
    while (hi > lo) {
      int mid = lo + (hi - lo + 1) / 2;
      int r = l + mid;
      ll sum = prefix[r] - prefix[l];
      (sum <= S) ? lo = mid : hi = mid - 1;
    }
    ll sum2 = prefix[l + lo + lo] - prefix[l + lo];
    while (sum2 > S) {
      lo--;
      sum2 = prefix[l + lo + lo] - prefix[l + lo];
    }
    cout << lo * 2 << '\n';
  }
}
