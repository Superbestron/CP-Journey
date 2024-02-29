#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(n), in_degree(n), vis(n);
  vector<vi> AL(n);
  set<ii> s;
  for (int i = 0; i < k; i++) {
    int src; cin >> src;
    vi output;
    for (int j = 1; j < n; j++) {
      int x; cin >> x; x--;
      output.push_back(x);
    }
    for (int j = 1; j < output.size(); j++) {
      if (s.count({output[j - 1], output[j]})) continue;
      s.insert({output[j - 1], output[j]});
      AL[output[j - 1]].push_back(output[j]);
      in_degree[output[j]]++;
    }
  }

  priority_queue<int, vi, greater<>> pq; // min priority queue
  for (int u = 0; u < n; ++u)
    if (in_degree[u] == 0) // next to be processed
      pq.push(u); // smaller index first
  while (!pq.empty()) { // Kahn’s algorithm
    int u = pq.top(); pq.pop(); // process u here
    vis[u] = true;
    for (auto &v : AL[u]) {
      --in_degree[v]; // virtually remove u->v
      if (in_degree[v] > 0) continue; // not a candidate, skip
      pq.push(v); // enqueue v in pq
    }
  }

  bool can = true;
  for (bool yes : vis) {
    if (!yes) {
      can = false;
    }
  }

  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
