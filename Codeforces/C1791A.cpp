#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    char c;
    string s = "codeforces";
    while (t--) {
        cin >> c;
        bool printed = false;
        for (char i : s) {
            if (i == c) {
                cout << "YES\n";
                printed = true;
                break;
            }
        }
        if (!printed) cout << "NO\n";
    }
}
