#include <bits/stdc++.h>
using namespace std;

/*
GETS:
V->number of vertices
E->number of edges
pair of vertices as edges (vertices are 1..V)

GIVES:
here_comes_santa_claus_validation_output.txt of edmonds() is the maximum matching
match[i] is matched pair of i (-1 if there isn't a matched pair)
 */

struct struct_edge {
  int v;
  struct_edge *n;
};

const int M = 500;
typedef struct_edge *edge;
struct_edge pool[M * M * 2];
edge top = pool, adj[M];
int V, E, match[M], qh, qt, q[M], father[M], base[M];
bool inq[M], inb[M], ed[M][M];

void add_edge(int u, int v) {
  top->v = v, top->n = adj[u], adj[u] = top++;
  top->v = u, top->n = adj[v], adj[v] = top++;
}

int LCA(int root, int u, int v) {
  static bool inp[M];
  memset(inp, 0, sizeof(inp));
  while (true) {
    inp[u = base[u]] = true;
    if (u == root) break;
    u = father[match[u]];
  }
  while (true) {
    if (inp[v = base[v]]) return v;
    else v = father[match[v]];
  }
}

void mark_blossom(int lca, int u) {
  while (base[u] != lca) {
    int v = match[u];
    inb[base[u]] = inb[base[v]] = true;
    u = father[v];
    if (base[u] != lca) father[u] = v;
  }
}

void blossom_contraction(int s, int u, int v) {
  int lca = LCA(s, u, v);
  memset(inb, 0, sizeof(inb));
  mark_blossom(lca, u);
  mark_blossom(lca, v);
  if (base[u] != lca) father[u] = v;
  if (base[v] != lca) father[v] = u;
  for (int u = 0; u < V; u++)
    if (inb[base[u]]) {
      base[u] = lca;
      if (!inq[u]) inq[q[++qt] = u] = true;
    }
}

int find_augmenting_path(int s) {
  memset(inq, 0, sizeof(inq));
  memset(father, -1, sizeof(father));
  for (int i = 0; i < V; i++) base[i] = i;
  inq[q[qh = qt = 0] = s] = true;
  while (qh <= qt) {
    int u = q[qh++];
    for (edge e = adj[u]; e; e = e->n) {
      int v = e->v;
      if (base[u] != base[v] && match[u] != v) {
        if ((v == s) || (match[v] != -1 && father[match[v]] != -1)) {
          blossom_contraction(s, u, v);
        } else if (father[v] == -1) {
          father[v] = u;
          if (match[v] == -1) return v;
          else if (!inq[match[v]]) inq[q[++qt] = match[v]] = true;
        }
      }
    }
  }
  return -1;
}

int augment_path(int s, int t) {
  int u = t, v, w;
  while (u != -1) {
    v = father[u];
    w = match[v];
    match[v] = u;
    match[u] = v;
    u = w;
  }
  return t != -1;
}

int edmonds() {
  int matchc = 0;
  memset(match, -1, sizeof(match));
  for (int u = 0; u < V; u++)
    if (match[u] == -1) matchc += augment_path(u, find_augmenting_path(u));
  return matchc;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int u, v, opp;
  cin >> V >> E;
  while (E--) {
    cin >> u >> v;
    if (!ed[u - 1][v - 1]) {
      add_edge(u - 1, v - 1);
      ed[u - 1][v - 1] = ed[v - 1][u - 1] = true;
    }
  }
  edmonds();

  // 2 cases
  // 1. If we find a perfect matching, let opponent start first, then we just greedily pick its corresponding
  //    matching vertex.
  // 2. If we don't, we start first by randomly picking a vertex that is "unmatched". As the opponent picks a vertex,
  //    we greedily pick its corresponding matching vertex. This works because there can never be 2 unmatched connected
  //    vertices, if not they would have already been matched by the algorithm.

  bool perfect = true;
  for (int i = 0; i < V; i++) {
    if (match[i] == -1) {
      perfect = false;
      cout << 1 << '\n';
      cout << i + 1 << '\n';
      cout.flush();
      break;
    }
  }

  if (perfect) {
    cout << 2 << '\n';
    cout.flush();
  }
  while (cin >> opp && opp != 0) {
    cout << match[opp - 1] + 1 << '\n';
    cout.flush();
  }
}
