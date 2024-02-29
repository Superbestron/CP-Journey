#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, m;
    string s, l, r;
    cin >> t;
    while (t--) {
        vector<set<int>> v(10);
        cin >> s >> m >> l >> r;
        for (int i = 0; i < s.size(); i++) {
            v[s[i] - '0'].insert(i);
        }
        bool can = false;
        int mini = 0;
        for (int i = 0; i < m; i++) {
            int curr_mini = mini;
            for (int lo = l[i] - '0'; lo <= r[i] - '0'; lo++) {
                if (v[lo].lower_bound(mini) == v[lo].end()) {
                    can = true;
                    goto done;
                }
                curr_mini = max(curr_mini, *v[lo].lower_bound(mini));
            }
            mini = curr_mini + 1;
        }
        done:
        if (can) cout << "YES\n";
        else cout << "NO\n";
    }
}

