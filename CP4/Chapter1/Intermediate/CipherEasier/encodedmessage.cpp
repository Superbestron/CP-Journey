#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    while (n--) {
        string s, ans;
        cin >> s;
        for (int i = sqrt(s.size()) - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j += sqrt(s.size())) {
                ans += s[j];
            }
        }
        cout << ans << '\n';
    }
}