#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<unordered_set<int>> vvi;

int n, m, a, b, num_scc = 0;
enum { UNVISITED = -1 };
vi dfs_num, S, scc_index;
vvi AL, AL_T;

void Kosaraju(int u, int pass) {
    dfs_num[u] = 1;
    unordered_set<int>& neighbour = (pass == 1) ? AL[u] : AL_T[u];
    for (int v : neighbour) {
        if (dfs_num[v] == UNVISITED) {
            Kosaraju(v, pass);
        }
    }
    if (pass == 1) S.push_back(u);
    else scc_index[u] = num_scc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    AL.assign(2 * m, {});
    AL_T.assign(2 * m, {});
    dfs_num.assign(2 * m, UNVISITED);
    scc_index.assign(2 * m, 0);
    // 2-SAT problem
    // a v b is ~a -> b and ~b -> a
    // a idx -> 2a - 1
    // ~a idx -> 2a - 2
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        if (a > 0 && b > 0) {
            AL[2 * a - 2].insert(2 * b - 1);
            AL[2 * b - 2].insert(2 * a - 1);
            AL_T[2 * b - 1].insert(2 * a - 2);
            AL_T[2 * a - 1].insert(2 * b - 2);
        } else if (a > 0 && b < 0) {
            b = -b;
            AL[2 * a - 2].insert(2 * b - 2);
            AL[2 * b - 1].insert(2 * a - 1);
            AL_T[2 * b - 2].insert(2 * a - 2);
            AL_T[2 * a - 1].insert(2 * b - 1);
        } else if (b > 0) {
            a = -a;
            AL[2 * a - 1].insert(2 * b - 1);
            AL[2 * b - 2].insert(2 * a - 2);
            AL_T[2 * b - 1].insert(2 * a - 1);
            AL_T[2 * a - 2].insert(2 * b - 2);
        } else {
            a = -a; b = -b;
            AL[2 * a - 1].insert(2 * b - 2);
            AL[2 * b - 1].insert(2 * a - 2);
            AL_T[2 * b - 2].insert(2 * a - 1);
            AL_T[2 * a - 2].insert(2 * b - 1);
        }
    }
    for (int u = 0; u < 2 * m; u++) {
        if (dfs_num[u] == UNVISITED) Kosaraju(u, 1);
    }
    dfs_num.assign(2 * m, UNVISITED);
    for (int i = 2 * m - 1; i >= 0; i--) {
        if (dfs_num[S[i]] == UNVISITED) {
            num_scc++;
            Kosaraju(S[i], 2);
        }
    }
    bool can = true;
    for (int i = 0; i < 2 * m; i += 2) {
        if (scc_index[i] == scc_index[i + 1]) {
            can = false;
            break;
        }
    }
    if (can) cout << "YES";
    else cout << "NO";
}