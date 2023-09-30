#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    string s;
    while (t--) {
        cin >> s;
        string ans;
        bool has_consec = false;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) {
                has_consec = true;
                break;
            }
        }
        if (s == "()") cout << "NO\n";
        else {
            if (has_consec) {
                for (int i = 0; i < s.size(); i++) {
                    ans += '(';
                    ans += ')';
                }
            } else {
                ans += string(s.size(), '(');
                ans += string(s.size(), ')');
            }
            cout << "YES\n" << ans << '\n';
        }
    }
}