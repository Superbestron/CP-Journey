#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef tuple<ll, ll> ii;
typedef tuple<ll, ll, ll, ll> iiii;

ll n, m, s, u, v, t0, p, d;
vector<vector<iiii>> AL;

bool can(ll x) {
  priority_queue<ii, vector<ii>, greater<>> pq;
  vi dist(n, 1e18);
  dist[0] = x;
  pq.emplace(x, 0);
  while (!pq.empty()) {
    auto [dt, curr] = pq.top(); pq.pop();
    if (dt > dist[curr]) continue;
    for (auto &[next, t, interval, w] : AL[curr]) {
      ll wait;
      if (dt >= t) wait = (interval - ((dt - t) % interval)) % interval;
      else wait = t - dt;
      if (dt + w + wait >= dist[next]) continue;
      dist[next] = dt + w + wait;
      pq.emplace(dist[next], next);
    }
  }
  return dist[n - 1] <= s;
}

int main() {
  cin >> n >> m >> s;
  AL.assign(n, {});
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> t0 >> p >> d;
    AL[u].emplace_back(v, t0, p, d);
  }
  ll lo = -1, hi = 1e14;
  while (hi > lo) {
    ll mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  if (lo == -1) cout << "impossible\n";
  else cout << lo << '\n';
}
