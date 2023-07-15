#include <bits/stdc++.h>

using namespace std;

int AM[150][150];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    while (cin >> n >> m >> q && !(n == 0 && m == 0 && q == 0)) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                AM[u][v] = 1e9;
            }
//            AM[u][u] = 0;
        }
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w;
            AM[u][v] = min(w, AM[u][v]);
        }
        for (int k = 0; k < n; k++)                    // loop order is k->u->v
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++) {
                    if ((AM[u][k] == 1e9) || (AM[k][v] == 1e9)) continue;
                    AM[u][v] = min(AM[u][v], AM[u][k] + AM[k][v]);
                }
        while (q--) {
            int src, dest;
            bool has_negative_cycle = false;
            cin >> src >> dest;
            for (int i = 0; i < n; i++) {
                if (AM[i][i] >= 0) continue;
                if (AM[src][i] != 1e9 && AM[i][dest] != 1e9) has_negative_cycle = true;
            }
            if (has_negative_cycle) cout << "-Infinity\n";
            else if (AM[src][dest] == 1e9) cout << "Impossible\n";
            else cout << AM[src][dest] << '\n';
        }
        cout << '\n';
    }
}