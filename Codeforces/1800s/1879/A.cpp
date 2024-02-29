#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> s(n), e(n);
        bool can = true;
        for (int i = 0; i < n; i++) {
            cin >> s[i] >> e[i];
        }
        int w = s[0], first_e = e[0];
        for (int i = 1; i < n; i++) {
            if (s[i] < w) continue;
            if (e[i] >= first_e) {
                can = false;
                break;
            }
        }
        if (can) cout << w << '\n';
        else cout << -1 << '\n';
    }
}

