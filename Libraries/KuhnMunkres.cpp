#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e9;
typedef vector<int> vi;
typedef vector<ll> vll;

class KuhnMunkres {  // Hungarian algorithm to find the maximum value PERFECT matching
 private:
  int L, V;
  int real_L, visited_cnt;  // increment visited_cnt before every count of aug
  vector<vll> AL;
  vll l;  // labels
  vi visited;
  vi S;  // vertices along the (partial) augmenting path
  vi inT;  // 1 if index in t, else 0. T is the set of vertices adjacent to augmenting path

  void expand_equality_subgraph() {
    ll min_delta = INF;
    for (const int &x : S) {
      for (int i = 0; i < L; i++) {
        if (inT[i] == 1) continue;  // we want not in T
        min_delta = min(min_delta, -AL[x][i] + l[x] + l[i + L]);
      }
    }
    for (const int &x : S) {
      l[x] -= min_delta;
    }
    for (int i = 0; i < L; i++) {
      if (inT[i] == 0) continue;  // we want in T
      l[i + L] += min_delta;
    }
  }

  int aug(int x) {
    if (visited[x] == visited_cnt) return 0;
    visited[x] = visited_cnt;
    S.push_back(x);
    for (int y = L; y < V; y++) {
      if (l[x] + l[y] != AL[x][y - L]) continue;  // not part of equality subgraph
      // Edit condition if used for floats

      inT[y - L] = 1;
      if (match[y] == -1 || aug(match[y])) {
        match[y] = x;
        match[x] = y;
        return 1;
      }
    }
    return 0;
  }

 public:
  vi match;  // match[i] = j means i is matched with j
  // Call hungarian with L <= R ie we try to match all the left vertices
  KuhnMunkres(int initL, int initR) : L(initR), V(2 * initR), real_L(initL) {
    // left from 0 to L - 1, right from L to 2L-1, vertices real_L to L - 1 are dummy
    AL.assign(L, vll(L, -INF));
    // Augment no-edge to be a large negative value
    // AL[i][j] is the edge weight from i to L + j
  }

  void add_edge(int u, int v, ll w) {  // u on the left, v on the right, 0 index
    AL[u][v] = w;
  }

  int max_matching() {
    l.assign(V, 0);  // each right vertex starts with label 0
    visited.assign(L, 0);
    visited_cnt = 0;
    for (int i = 0; i < L; i++) {
      // for each left vertex, assign label to the the largest weight edge
      l[i] = -INF;
      for (int j = 0; j < L; j++) {
        l[i] = max(l[i], AL[i][j]);
      }
    }

    match.assign(V, -1);
    for (int i = 0; i < real_L; i++) {
      if (match[i] != -1) continue;
      while (true) {
        S.clear();
        inT.assign(L, 0);
        visited_cnt++;
        int res = aug(i);
        if (res) {
          break;
        }
        // Else we need to expand the equality subgraph
        expand_equality_subgraph();
      }
    }
    ll totalmatching = 0;
    for (int i = 0; i < real_L; i++) {
      totalmatching += AL[i][match[i] - L];
    }

    return totalmatching;
  }
};
