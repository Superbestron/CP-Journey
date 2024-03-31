#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef long double ld;
typedef vector<ii> vii;
typedef pair<ll, int> lli;
typedef pair<ld, ld> ldld;
typedef vector<bool> vb;
typedef pair<ll, ll> pll;

const int INF = 1e9;
const ll LONG_INF = 1e18;

#define FOR(i, R) for (int i = 0; i < R; ++i)

void solve() {
  ll N, m, c;
  cin >> N >> m >> c;
  int A, B, v, t, l, r;
  vector<vi> neighbour[N];
  FOR(i, N) neighbour[i] = vector<vi>();

  FOR(i, m) {
    cin >> A >> B >> t >> l >> r;
    --A;
    --B;
    neighbour[A].push_back({B, t, l, r});
    neighbour[B].push_back({A, t, l, r});
  }

  vll dist(N, LONG_INF);
  dist[0] = 0LL;
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.emplace(0LL, 0);

  ll actual_w, wait, cur_time;

  while (!pq.empty()) {                          // main loop
    auto [d, u] = pq.top();
    pq.pop();            // shortest unvisited u
    if (d > dist[u]) continue;                   // a very important check
    cur_time = d % c;
    for (vector<int> &vec : neighbour[u]) {

      v = vec[0];
      t = vec[1];
      l = vec[2];
      r = vec[3];

      if (l <= cur_time && cur_time <= r) wait = 0LL;
      else if (cur_time < l) wait = l - cur_time;
      else wait = l - cur_time + c;

      actual_w = wait + t;
      if (dist[u] + actual_w >= dist[v]) continue;        // not improving, skip
      dist[v] = dist[u] + actual_w;                       // relax operation
      pq.push({dist[v], v});                     // enqueue better pair
    }
  }

  cout << dist[N - 1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
