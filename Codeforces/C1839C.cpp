#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n;
        set<int> s;
        for (int i = 0; i < n; i++) {
            cin >> k;
            if (k == 0) s.insert(i);
        }
        if (!s.count(n - 1)) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        vector<int> ans;
        int prev_idx = 0;
        for (int idx : s) {
            ans.push_back(idx - prev_idx);
            for (int i = prev_idx; i < idx; i++) ans.push_back(0);
            prev_idx = idx + 1;
        }
        reverse(ans.begin(), ans.end());
        for (int i : ans) cout << i << ' ';
        cout << '\n';
    }
}