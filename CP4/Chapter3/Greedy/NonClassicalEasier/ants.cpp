#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, l, n, pos; cin >> t;
    while (t--) {
        cin >> l >> n;
        int mini = 0, maxi = 0;
        while (n--) {
            cin >> pos;
            mini = max(mini, min(pos, l - pos));
            maxi = max(maxi, max(pos, l - pos));
        }
        cout << mini << ' ' << maxi << '\n';
    }
}