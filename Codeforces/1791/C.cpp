#include <bits/stdc++.h>

using namespace std;

deque<bool> d;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    string s;
    while (t--) {
        cin >> n >> s;
        d.clear();
        for (char i : s) {
            d.push_back(i == 1);
        }
        int ans = s.size();
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - i - 1]) {
                ans -= 2;
            } else break;
        }
        cout << ans << '\n';
    }
}
