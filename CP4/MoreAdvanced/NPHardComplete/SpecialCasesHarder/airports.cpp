#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;

vi match, vis;
vector<vi> AL;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s, f, t;
  cin >> n >> m;
  vi inspection(n);
  vector<iii> flights;
  for (int& i : inspection) cin >> i;
  vector<vi> dist(n, vi(n)), APSP(n, vi(n));
  int V = 2 * m, Vleft = m;
  AL.assign(V, {});
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> dist[i][j];
      if (i == j) APSP[i][j] = dist[i][j];
      else APSP[i][j] = dist[i][j] + inspection[j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        APSP[i][j] = min(APSP[i][j], APSP[i][k] + APSP[k][j]);
      }
    }
  }
  for (int i = 0; i < m; i++) {
    cin >> s >> f >> t;
    s--; f--;
    flights.emplace_back(s, f, t);
  }

  // construct graph
  // only have an edge if a plane is able to finish its flight and also start another flight
  for (int i = 0; i < m; i++) {
    auto& flight1 = flights[i];
    for (int j = 0; j < m; j++) {
      if (i != j) {
        auto& flight2 = flights[j];
        int finish_flight1_time = get<2>(flight1) + dist[get<0>(flight1)][get<1>(flight1)]
            + inspection[get<1>(flight1)];
        int shortest_time_to_flight2_airport = APSP[get<1>(flight1)][get<0>(flight2)];
        if (finish_flight1_time + shortest_time_to_flight2_airport <= get<2>(flight2)) {
          AL[i].push_back(j + m);
        }
      }
    }
  }

  unordered_set<int> freeV;
  for (int L = 0; L < Vleft; ++L)
    freeV.insert(L);                             // initial assumption
  match.assign(V, -1);

  int MCBM = 0;
  // Greedy pre-processing for trivial Augmenting Paths
  // try commenting versus un-commenting this for-loop
  for (int L = 0; L < Vleft; ++L) {              // O(V+E)
    vi candidates;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int)candidates.size() > 0) {
      ++MCBM;
      freeV.erase(L);                            // L is matched
      int a = rand()%(int)candidates.size();     // randomize this
      match[candidates[a]] = L;
    }
  }                                                  // for each free vertex
  for (int L : freeV) {                        // (in random order)
    vis.assign(Vleft, 0);                        // reset first
    MCBM += Aug(L);                              // try to match f
  }
  cout << m - MCBM << '\n';
}
