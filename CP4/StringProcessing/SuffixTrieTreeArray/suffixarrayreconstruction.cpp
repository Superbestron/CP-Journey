#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, l, s; cin >> t;
    string temp;
    while (t--) {
        cin >> l >> s;
        char str[l]; str[l] = '\0';
        memset(str, '$', sizeof str);
        bool printed = false;
        for (int i = 0; i < s; i++) {
            int idx, ctr = 0;
            cin >> idx >> temp;
            idx--;
            if (printed) continue;
            // do from left till hit '*'
            while (ctr < temp.size() && temp[ctr] != '*') {
                if (str[idx + ctr] == '$') str[idx + ctr] = temp[ctr];
                else if (str[idx + ctr] != temp[ctr]) {
                    printed = true;
                }
                ctr++;
            }
            // do from right
            int r_ctr = temp.size() - 1;

            while (r_ctr > ctr) {
                if (str[l - (temp.size() - r_ctr)] == '$') str[l - (temp.size() - r_ctr)] = temp[r_ctr];
                else if (str[l - (temp.size() - r_ctr)] != temp[r_ctr]) {
                    printed = true;
                }
                r_ctr--;
            }
        }
        if (printed) cout << "IMPOSSIBLE";
        else {
            bool all_pass = true;
            for (char c : str) {
                if (c == '$') {
                    all_pass = false;
                    break;
                }
            }
            if (all_pass) cout << str;
            else cout << "IMPOSSIBLE";
        }
        cout << '\n';
    }
}