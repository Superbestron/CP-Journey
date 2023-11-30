#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

const double EPS = 1e-9;
int N, M, X, C1, C2, T;
ll shortest_path;
ld max_path;
vector<vector<ii>> AL;

bool can(ll x) {
  priority_queue<ii, vector<ii>, greater<>> pq;
  vi dist(N, 1e18);
  dist[N - 1] = 0;
  pq.emplace(0, N - 1);
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto &[v, w] : AL[u]) {
      if (w > x) continue;
      if (d + w < dist[v]) {
        dist[v] = d + w;
        pq.emplace(dist[v], v);
      }
    }
  }
  return max_path - dist[0] > EPS;
}

int main() {
  cin >> N >> M >> X;
  AL.assign(N, {});
  vi dist(N, 1e18);
  for (int i = 0; i < M; i++) {
    cin >> C1 >> C2 >> T;
    C1--;
    C2--;
    AL[C1].emplace_back(C2, T);
    AL[C2].emplace_back(C1, T);
  }
  priority_queue<ii, vector<ii>, greater<>> pq;
  dist[N - 1] = 0;
  pq.emplace(0, N - 1);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u]) continue;
    for (auto &[v, w] : AL[u]) {
      if (d + w < dist[v]) {
        dist[v] = d + w;
        pq.emplace(dist[v], v);
      }
    }
  }
  shortest_path = dist[0];
  max_path = shortest_path + (ld) X / 100 * shortest_path;

  ll lo = 0, hi = 1e18;
  while (hi > lo) {
    ll mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  cout << lo << '\n';
}
