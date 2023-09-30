#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    string s1, s2;
    while (t--) {
        cin >> s1 >> s2;
        bool can = false;
        for (int i = 0; i < s1.size() - 1; i++) {
            if (s1[i] == '0' && s1[i + 1] == '1' && s2[i] == '0' && s2[i + 1] == '1') {
                can = true;
                break;
            }
        }
        if (can) cout << "YES\n";
        else cout << "NO\n";
    }
}

