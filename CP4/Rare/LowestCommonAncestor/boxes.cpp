#include <bits/stdc++.h>
#define MAX_N 200001

using namespace std;
typedef vector<int> vi;

int L[2 * MAX_N], E[2 * MAX_N], H[MAX_N], sz[MAX_N], idx = 0;
vector<vector<int>> AL;

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

int dfs(int cur, int depth) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    int sum = 1;
    for (auto &nxt : AL[cur]) {
        sum += dfs(nxt, depth + 1);
        E[idx] = cur;                              // backtrack to current node
        L[idx++] = depth;
    }
    sz[cur] = sum;
    return sum;
}

void buildRMQ() {
    sz[0] = 1;
    dfs(0, 0);                       // we assume that the root is at index 0
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q, d, l;
    cin >> N;
    N++;
    AL.assign(N, {});
    memset(sz, -1, sizeof sz);
    for (int i = 1; i < N; i++) {
        cin >> d;
        AL[d].push_back(i);
    }
    buildRMQ();
    vi L_v(L,  L + 2 * N);
    SparseTable SpT(L_v);
    cin >> Q;
    while (Q--) {
        int boxes = 0;
        cin >> l;
        vector<int> num(l);
        for (int i = 0; i < l; i++) cin >> num[i];
        for (auto i : num) {
            bool biggest = true;
            for (auto j : num) {
                if (i == j) continue;
                if (E[SpT.RMQ(min(H[i], H[j]), max(H[i], H[j]))] == j) {
                    biggest = false;
                    break;
                }
            }
            if (biggest) boxes += sz[i];
        }
        cout << boxes << '\n';
    }
}