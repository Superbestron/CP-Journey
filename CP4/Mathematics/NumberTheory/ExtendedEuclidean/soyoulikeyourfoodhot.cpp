#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string pt_d, p1_d, p2_d;
  cin >> pt_d >> p1_d >> p2_d;
  pt_d.erase(pt_d.size() - 3, 1);
  p1_d.erase(p1_d.size() - 3, 1);
  p2_d.erase(p2_d.size() - 3, 1);
  ll pt = stoi(pt_d), p1 = stoi(p1_d), p2 = stoi(p2_d);
  ll x, y;
  ll a = extEuclid(p1, p2, x, y);
  vector<pair<int, int>> ans;
  if (pt % a == 0) {
    x *= (pt / a); y *= (pt / a);
    if (x > y) {
      while (x >= 0) {
        if (y >= 0) ans.emplace_back(x, y);
        x -= p2 / a;
        y += p1 / a;
      }
      reverse(ans.begin(), ans.end());
      for (auto& [one, two] : ans) cout << one << ' ' << two << '\n';
    } else {
      while (y >= 0) {
        if (x >= 0) cout << x << ' ' << y << '\n';
        x += p2 / a;
        y -= p1 / a;
      }
    }
  } else {
    cout << "none";
  }
}