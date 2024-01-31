#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n, ai, di;

void solve() {
  cin >> n;
  vi a, d;
  set<int> alive, affected;
  a.push_back(0); d.push_back(1e9); alive.insert(0);
  for (int i = 1; i <= n; i++) {
    alive.insert(i);
    affected.insert(i);
    cin >> ai;
    a.push_back(ai);
  }
  for (int i = 1; i <= n; i++) {
    cin >> di;
    d.push_back(di);
  }
  a.push_back(0); d.push_back(1e9); alive.insert(n + 1);
  for (int i = 0; i < n; i++) {
    vi del;
    set<int> temp;
    for (int idx : affected) {
      if (idx == 0 || idx == n + 1) continue;
      if (!alive.count(idx)) continue;
      int pre = *prev(alive.lower_bound(idx)), nxt = *alive.upper_bound(idx);
      if (a[pre] + a[nxt] > d[idx]) {
        temp.insert(pre); temp.insert(nxt);
        del.push_back(idx);
      }
    }
    swap(affected, temp);
    for (int j : del) alive.erase(j);
    cout << del.size() << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
