#include <bits/stdc++.h>

using namespace std;

bool AM[200][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    while (t--) {
        cin >> n; n += 2;
        vector<pair<int, int>> coords(n);
        for (int i = 0; i < n; i++) {
            cin >> coords[i].first >> coords[i].second;
        }
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                AM[u][v] = false;
            }
            AM[u][u] = true;
        }

        for (int u = 0; u < n - 1; u++) {
            for (int v = u + 1; v < n; v++) {
                auto& s = coords[u], d = coords[v];
                AM[u][v] = AM[v][u] = (abs(s.first - d.first) + abs(s.second - d.second)) <= 1000;
            }
        }

        for (int a = 0; a < n; a++)                    // loop order is k->u->v
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++) {
                    AM[u][v] |= (AM[u][a] & AM[a][v]);
                }

        if (AM[0][n - 1]) cout << "happy\n";
        else cout << "sad\n";
    }
}