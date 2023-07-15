#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, D, M, days; cin >> T;
    while (T--) {
        cin >> D >> M;
        int start = 1, ans = 0;
        for (int i = 0; i < M; i++) {
            cin >> days;
            if (days >= 13) ans += (13 + start) % 7 == 0 ? 1 : 0;
            start = (days + start) % 7;
        }
        cout << ans << '\n';
    }
}