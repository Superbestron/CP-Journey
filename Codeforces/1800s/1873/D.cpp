#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        string s;
        cin >> s;
        int ctr = 0, ans = 0;
        while (ctr < s.size()) {
            if (s[ctr] == 'W') {
                ctr++;
                continue;
            }
            ans++;
            ctr += k;
        }
        cout << ans << '\n';
    }
}