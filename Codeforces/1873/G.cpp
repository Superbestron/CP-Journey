#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    string s;
    cin >> t;
    while (t--) {
        cin >> s;
        int ans = 0, curr_size = 0, smallest_size = INT32_MAX;
        bool consec_B = false;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (i != 0 && s[i - 1] == s[i] && s[i - 1] == 'B') consec_B = true;
            if (c == 'A') {
                ans++;
                curr_size++;
            } else {
                if (curr_size == 0) continue;
                smallest_size = min(smallest_size, curr_size);
                curr_size = 0;
            }
        }
        if (curr_size) {
            smallest_size = min(smallest_size, curr_size);
        }
        if (!consec_B && (s[0] == 'A' && s.back() == 'A')) cout << ans - smallest_size << '\n';
        else cout << ans << '\n';
    }
}