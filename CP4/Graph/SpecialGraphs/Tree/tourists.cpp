//#include <bits/stdc++.h>
//using namespace std;
//
//vector<vector<int>> children;
//
//vector<int> L, E, H, dist;
//int idx;
//
//typedef vector<int> vi;
//
//class SparseTable {                              // OOP style
//private:
//    vi A, P2, L2;
//    vector<vi> SpT;                                // the Sparse Table
//public:
//    SparseTable(vi &initialA) {                    // pre-processing routine
//        A = initialA;
//        int n = (int)A.size();
//        int L2_n = (int)log2(n)+1;
//        P2.assign(L2_n, 0);
//        L2.assign(1<<L2_n, 0);
//        for (int i = 0; i <= L2_n; ++i) {
//            P2[i] = (1<<i);                            // to speed up 2^i
//            L2[(1<<i)] = i;                            // to speed up log_2(i)
//        }
//        for (int i = 2; i < P2[L2_n]; ++i)
//            if (L2[i] == 0)
//                L2[i] = L2[i-1];                         // to fill in the blanks
//
//        // the initialization phase
//        SpT = vector<vi>(L2[n]+1, vi(n));
//        for (int j = 0; j < n; ++j)
//            SpT[0][j] = j;                             // RMQ of sub array [j..j]
//
//        // the two nested loops below have overall time complexity = O(n log n)
//        for (int i = 1; P2[i] <= n; ++i)             // for all i s.t. 2^i <= n
//            for (int j = 0; j+P2[i]-1 < n; ++j) {      // for all valid j
//                int x = SpT[i-1][j];                     // [j..j+2^(i-1)-1]
//                int y = SpT[i-1][j+P2[i-1]];             // [j+2^(i-1)..j+2^i-1]
//                SpT[i][j] = A[x] <= A[y] ? x : y;
//            }
//    }
//
//    int RMQ(int i, int j) {
//        int k = L2[j-i+1];                           // 2^k <= (j-i+1)
//        int x = SpT[k][i];                           // covers [i..i+2^k-1]
//        int y = SpT[k][j-P2[k]+1];                   // covers [j-2^k+1..j]
//        return A[x] <= A[y] ? x : y;
//    }
//};
//
//void dfs(int cur, int depth) {
//    H[cur] = idx;
//    E[idx] = cur;
//    L[idx++] = depth;
//    for (auto &nxt : children[cur]) {
////        cout << nxt << '\n';
//        if (dist[nxt] != -1) continue;
//        dist[nxt] = dist[cur] + 1;
//        dfs(nxt, depth + 1);
//        E[idx] = cur;                              // backtrack to current node
//        L[idx++] = depth;
//    } }
//
//void buildRMQ() {
//    idx = 0;
//    dist[0] = 0;
//    dfs(0, 0);                       // we assume that the root is at index 0
//}
//
//int main() {
//    int n, a, b, ans = 0;
//    cin >> n;
//    children.assign(n, vector<int>());
//    L.assign(2 * n, 0);
//    E.assign(2 * n, 0);
//    H.assign(n, -1);
//    dist.assign(n, -1);
//    for (int i = 0; i < n - 1; i++) {
//        cin >> a >> b;
//        a--;
//        b--;
//        children[a].push_back(b);
//        children[b].push_back(a);
//    }
//    buildRMQ();
//    SparseTable SpT(L);
//    for (int i = 1; i <= n; i++) {
//        for (int j = 2 * i; j <= n; j += i) {
//            int lca = E[SpT.RMQ(min(H[i - 1], H[j - 1]), max(H[i - 1], H[j - 1]))];
//            ans += dist[i - 1] + dist[j - 1] - dist[lca] * 2 + 1;
//        }
//    }
//    cout << ans;
//}