#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    string type, curr;
    while (T--) {
        cin >> type;
        int ans = INT32_MAX;
        for (int i = 0; i < 4; i++) {
            cin >> curr;
            int j = 0;
            for (; j < min(curr.size(), type.size()); j++) {
                if (curr[j] != type[j]) break;
            }
            int total = type.size() + curr.size() - 2 * j;
            ans = min(ans, total + (i ? 1 : 0));
        }
        cout << ans << '\n';
    }
}