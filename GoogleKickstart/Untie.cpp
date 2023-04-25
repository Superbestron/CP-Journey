#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    string s;
    for (int t = 1; t <= T; t++) {
        cin >> s;
        int limit = s.size() - 1, ctr = 0, ans = 0;
        char prev = ' ';
        while (limit >= 0 && s[0] == s[limit]) {
            limit--; ctr++; prev = s[0];
        }
        if (limit == -1) ans = ceil(ctr * 1.0 / 2);
        else {
            for (int i = 0; i <= limit; i++) {
                if (s[i] == prev) ctr++;
                else {
                    ans += ctr / 2;
                    ctr = 1;
                    prev = s[i];
                }
            }
            ans += ctr / 2;
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
}

