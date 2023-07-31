#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string key;
    while (cin >> n && n != 0) {
        cin.ignore();
        getline(cin, key);
        string stripped;
        for (char i : key) {
            if (i == ' ') continue;
            stripped += toupper(i);
        }
        int sz = stripped.size();
        if (n >= sz) {
            cout << stripped << '\n';
            continue;
        }
        string ans(sz, ' ');
        for (int base = 0, idx = 0; idx < sz; base++) {
            int ctr = base;
            while (ctr < sz) {
                ans[ctr] = stripped[idx++];
                ctr += n;
            }
        }
        cout << ans << '\n';
    }
}