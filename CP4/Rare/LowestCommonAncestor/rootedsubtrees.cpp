#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vector<vi> children;

vi L, E, H;
int idx;

// If you are following CP4's implementation of Sparse Table, it's buggy
// Follow mine

class SparseTable {                              // OOP style
private:
    vector<vi> SpT;                                // the Sparse Table
    vi A;
    int N, K;
public:
    SparseTable(vi &initialA) {                    // pre-processing routine
        A = initialA;
        N = initialA.size();
        K = MSB(N);

        SpT = vector<vi>(K, vi(N));
        for (int j = 0; j < N; j++) {
            SpT[0][j] = j;
        }
        for (int i = 1; i < K; i++) {
            for (int j = 0; j + (1 << i) - 1 < N; j++) {
                int x = SpT[i - 1][j];
                int y = SpT[i - 1][j + (1 << (i - 1))];
                SpT[i][j] = A[x] <= A[y] ? x : y;
            }
        }
    }

    inline int MSB(unsigned int x) { return 32 - __builtin_clz(x); }

    int RMQ(int i, int j) {
        int k = MSB(j - i + 1) - 1;
        int x = SpT[k][i];
        int y = SpT[k][j - (1 << k) + 1];
        return A[x] <= A[y] ? x : y;
    }
};

void dfs(int cur, int depth) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    for (auto &nxt : children[cur]) {
        if (H[nxt] != -1) continue;
        dfs(nxt, depth + 1);
        E[idx] = cur;                              // backtrack to current node
        L[idx++] = depth;
    }
}

void buildRMQ() {
    idx = 0;
    dfs(0, 0);                       // we assume that the root is at index 0
}

int main() {
    int n, q, a, b;
    cin >> n >> q;
    children.assign(n, vector<int>());
    L.assign(2 * n, 0);
    E.assign(2 * n, 0);
    H.assign(n, -1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--;
        b--;
        children[a].push_back(b);
        children[b].push_back(a);
    }
    buildRMQ();
    SparseTable SpT(L);
    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        a--; b--;
        int lca = E[SpT.RMQ(min(H[a], H[b]), max(H[a], H[b]))];
        long long dist = L[H[a]] + L[H[b]] - L[H[lca]] * 2 + 1;
        cout << (long long) n - dist + dist * (dist + 1) / 2 << '\n';
    }
}