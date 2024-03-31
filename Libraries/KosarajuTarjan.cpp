#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

enum { UNVISITED = 0, VISITED = 1 };

vector<vi> AL, AL_T;
vi S, dfs_num, scc_index;
int N, num_scc = 0;

void kosaraju(int u, int pass) {
  dfs_num[u] = VISITED;
  vi &neighbours = (pass == 1) ? AL[u] : AL_T[u];
  for (auto& v : neighbours) {
    if (dfs_num[v] == UNVISITED) kosaraju(v, pass);
  }
  if (pass == 1) S.push_back(u);
  else scc_index[u] = num_scc;
}

//int dfsNumberCounter, numSCC; // global variables
//vi dfs_num, dfs_low, visited;
//stack<int> St;
//
//void tarjanSCC(int u) {
//  dfs_low[u] = dfs_num[u] = dfsNumberCounter; // dfs_low[u]<=dfs_num[u]
//  dfsNumberCounter++; // increase counter
//  St.push(u); // remember the order
//  visited[u] = 1;
//  for (auto &[v, w] : AL[u]) {
//    if (dfs_num[v] == UNVISITED)
//      tarjanSCC(v);
//    if (visited[v]) // condition for update
//      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
//  }
//  if (dfs_low[u] == dfs_num[u]) { // a root/start of an SCC
//    ++numSCC; // when recursion unwinds
//    while (1) {
//      int v = St.top(); St.pop();
//      visited[v] = 0;
//      if (u == v) break;
//    }
//  }
//}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  scc_index.assign(N, 0);
  num_scc = 0;
  S.clear();
  dfs_num.assign(N, UNVISITED);
  for (int u = 0; u < N; u++) {
    if (dfs_num[u] == UNVISITED) kosaraju(u, 1);
  }
  dfs_num.assign(N, UNVISITED);
  for (int i = N - 1; i >= 0; i--) {
    if (dfs_num[S[i]] == UNVISITED) {
      kosaraju(S[i], 2);
      num_scc++;
    }
  }

//  dfs_num.assign(N, UNVISITED);
//  dfs_low.assign(N, 0);
//  visited.assign(N, 0);
//  while (!St.empty()) St.pop();
//  dfsNumberCounter = numSCC = 0;
//  for (int u = 0; u < N; ++u)
//    if (dfs_num[u] == UNVISITED)
//      tarjanSCC(u);
}
