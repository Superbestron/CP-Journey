#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    deque<ll> d;
    sort(a.begin(), a.end());
    for (int i : a) d.push_back(i);
    ll accum = 0, ans = 0;
    while (d.size() > 1) {
      ll& top = d.back();
      ll& front = d.front();
      // accum < top
      if (accum + front >= top) {
        ll toMinus = min(front, top - accum);
        accum += toMinus;
        ans += toMinus;
        front -= toMinus;
        ans++; // combo
        accum -= top;
        d.pop_back();
      } else {
        accum += front;
        ans += front;
        front = 0;
      }
      if (front == 0) d.pop_front();
    }
    if (d.empty()) {
      cout << ans << '\n';
    } else {
      ll left = d.front();
      if (left == 1) cout << ans + 1 << '\n';
      else {
        left -= accum;
        cout << ans + (left + 1) / 2 + 1 << '\n';
      }
    }
  }
}
