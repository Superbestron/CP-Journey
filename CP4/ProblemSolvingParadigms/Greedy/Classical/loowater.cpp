#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && n != 0 && m != 0) {
        int D[n], H[m];
        for (int i = 0; i < n; i++) cin >> D[i];
        for (int i = 0; i < m; i++) cin >> H[i];
        sort(D, D + n);
        sort(H, H + m);
        int gold = 0, d = 0, k = 0;
        while ((d < n) && (k < m)) {
            while ((k < m) && D[d] > H[k]) k++;
            if (k == m) break;
            gold += H[k];
            d++; k++;
        }
        if (d == n) cout << gold << '\n';
        else cout << "Loowater is doomed!" << '\n';
    }
}