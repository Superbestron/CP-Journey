#include <bits/stdc++.h>

using namespace std;

double AM[100][100];
const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, x, y, src, dest;
    while (cin >> n && n != 0) {
        vector<pair<int, int>> coords(n);
        for (int i = 0; i < n; i++) {
            cin >> coords[i].first >> coords[i].second;
        }
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                AM[u][v] = 1e9;
            }
            AM[u][u] = 0;
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> src >> dest;
            auto& s = coords[src], d = coords[dest];
            AM[src][dest] = AM[dest][src] = sqrt(pow(s.first - d.first, 2) + pow(s.second - d.second, 2));
        }

        for (int a = 0; a < n; a++)                    // loop order is k->u->v
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++) {
                    AM[u][v] = min(AM[u][v], AM[u][a] + AM[a][v]);
                }

        double original = 0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++) original += AM[u][v];

        double mini = 1e9;
        pair<int, int> p;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                auto& s = coords[u], d = coords[v];
                double total = 0, temp = AM[u][v];
                double shortest_dist = sqrt(pow(s.first - d.first, 2) + pow(s.second - d.second, 2));
                if (AM[u][v] - shortest_dist < EPS) continue; // already have road
                AM[u][v] = AM[v][u] = sqrt(pow(s.first - d.first, 2) + pow(s.second - d.second, 2));
                for (int a = 0; a < n; ++a) {
                    for (int b = a + 1; b < n; ++b) {
                        total += min(AM[a][b], min(AM[b][u] + AM[u][v] + AM[v][a], AM[a][u] + AM[u][v] + AM[v][b]));
                    }
                }
                AM[u][v] = AM[v][u] = temp;
                if (total < mini) {
                    mini = total;
                    p = make_pair(u, v);
                }
            }
        }

        cout << fixed << setprecision(5);
        if (original - mini < EPS) cout << "no addition reduces " << original << '\n';
        else cout << "adding " << p.first << ' ' << p.second << " reduces " << original << " to " << mini << '\n';
    }
}