#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int N, n, m, num_scc = 0;
enum { UNVISITED = -1 };
vi dfs_num, S, scc_index;
vvi AL, AL_T, AL_DAG, sccs;

void Kosaraju(int u, int pass) {
  dfs_num[u] = 1;
  vi &neighbour = (pass == 1) ? AL[u] : AL_T[u];
  for (int v : neighbour) {
    if (dfs_num[v] == UNVISITED) {
      Kosaraju(v, pass);
    }
  }
  if (pass == 1) S.push_back(u);
  else {
    scc_index[u] = num_scc;
    sccs[num_scc].push_back(u);
  }
}

int parse_guest(string x) {
  int num = stoi(x.substr(0, x.size() - 1));
  if (x.back() == 'h')
    return num;
  else
    return num + n;
}

int not_vertex(int a) {
  if (a < n) return a + n;
  return a - n;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  N = 2 * n;
  string s1, s2;
  AL.assign(N, {});
  AL_T.assign(N, {});
  AL_DAG.assign(N, {});
  dfs_num.assign(N, UNVISITED);
  scc_index.assign(N, 0);
  sccs.assign(N, {});

  // 2-SAT problem
  // a v b is ~a -> b and ~b -> a
  // a idx -> idx
  // ~a idx -> idx + n
  // Take an assignment as true if a husband can sit on same side as 0w
  for (int i = 0; i < m; i++) {
    cin >> s1 >> s2;
    int idx1 = parse_guest(s1);
    int idx2 = parse_guest(s2);
    AL[not_vertex(idx1)].push_back(idx2);
    AL[not_vertex(idx2)].push_back(idx1);
    AL_T[idx2].push_back(not_vertex(idx1));
    AL_T[idx1].push_back(not_vertex(idx2));
  }
  AL[0].push_back(not_vertex(0));  // force 0h to be false (0h cannot sit at the same side as 0w)

  for (int u = 0; u < N; u++) {
    if (dfs_num[u] == UNVISITED) Kosaraju(u, 1);
  }
  dfs_num.assign(N, UNVISITED);
  for (int i = N - 1; i >= 0; i--) {
    if (dfs_num[S[i]] == UNVISITED) {
      Kosaraju(S[i], 2);
      num_scc++;
    }
  }
  for (int i = 1; i < n; i++) {
    if (scc_index[i] == scc_index[i + n]) {
      cout << "bad luck\n";
      return 0;
    }
  }

  // Compress SCCs to DAG nodes
  for (int u = 0; u < N; u++) {
    for (int v : AL[u]) {
      if (scc_index[u] == scc_index[v]) continue;
      AL_DAG[scc_index[u]].push_back(scc_index[v]);
    }
  }

  vi truth_values(n, UNVISITED);
  for (int i = num_scc - 1; i >= 0; i--) {
    for (int v : sccs[i]) {
      if (v < n) {
        if (truth_values[v] == UNVISITED) truth_values[v] = 1;
      } else {
        if (truth_values[v - n] == UNVISITED) truth_values[v - n] = 0;
      }
    }
  }

  for (int i = 1; i < n; i++) {
    if (truth_values[i]) cout << i << "h ";
    else cout << i << "w ";
  }
}
