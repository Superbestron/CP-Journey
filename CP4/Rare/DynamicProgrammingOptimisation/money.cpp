#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

vii pro, con, prof, conf;

// Divide and conquer approach to tackle this geometry problem
// Essentially, finding largest rectangle
// Referenced from Brandon Tang

ll recurse(int pL, int pR, int cL, int cR) {
  if (pL > pR) return 0;
  if (cL > cR) return 0;

  int mid = (pL + pR) / 2;
  ll ans = 0;
  int idx;

  for (int i = cL; i <= cR; i++) {
    if (conf[i].first <= prof[mid].first) {
      idx = i;
      continue;
    }

    ll cur = (conf[i].first - prof[mid].first) * (conf[i].second - prof[mid].second);
    if (cur > ans) {
      ans = cur;
      idx = i;
    }
  }
  return max(max(recurse(pL, mid - 1, cL, idx), recurse(mid + 1, pR, idx, cR)), ans);
}

int main() {
  int m, n;
  cin >> m >> n;
  for (ll i = 0; i < m; i++) {
    ll p, d;
    cin >> p >> d;
    pro.emplace_back(d, p);
  }
  for (ll i = 0; i < n; i++) {
    ll q, e;
    cin >> q >> e;
    con.emplace_back(e, q);
  }
  sort(pro.begin(), pro.end());
  sort(con.begin(), con.end(), greater<>());

  prof.push_back(pro[0]);
  for (int i = 1; i < m; i++) {
    if (pro[i].second >= prof.back().second) continue;  // if same price, always take the one that starts earlier
    prof.emplace_back(pro[i].first, pro[i].second);
  }
  conf.push_back(con[0]);
  for (int i = 1; i < n; i++) {
    if (con[i].second <= conf.back().second) continue;  // if same price, always take the one that ends later
    conf.emplace_back(con[i].first, con[i].second);
  }
  reverse(conf.begin(), conf.end());
  cout << recurse(0, prof.size() - 1, 0, conf.size() - 1) << '\n';
}
