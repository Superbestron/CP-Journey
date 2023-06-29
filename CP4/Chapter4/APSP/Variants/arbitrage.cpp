#include <bits/stdc++.h>

using namespace std;

double AM[200][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    double x, y;
    char temp;
    string country, src, dest;
    while (cin >> n && n != 0) {
        unordered_map<string, int> name_to_int;
        unordered_map<int, string> int_to_name;
        for (int i = 0; i < n; i++) {
            cin >> country;
            name_to_int[country] = i;
            int_to_name[i] = country;
        }
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                AM[u][v] = 1e9;
            }
            AM[u][u] = 0;
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> src >> dest >> x >> temp >> y;
            int s = name_to_int[src], d = name_to_int[dest];
            double ratio = y / x;
            AM[s][d] = -log(ratio);
        }

        for (int k = 0; k < n; k++)                    // loop order is k->u->v
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++)
                    AM[u][v] = min(AM[u][v], AM[u][k] + AM[k][v]);

        bool arbitrage = false;
        for (int k = 0; k < n; k++) if (AM[k][k] < 0) arbitrage = true;
        if (arbitrage) cout << "Arbitrage\n";
        else cout << "Ok\n";
    }
}