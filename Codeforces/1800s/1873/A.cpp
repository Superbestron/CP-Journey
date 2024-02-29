#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int diff = 0;
        if (s[0] != 'a') diff++;
        if (s[1] != 'b') diff++;
        if (s[2] != 'c') diff++;
        if (diff == 3) cout << "NO\n";
        else cout << "YES\n";
    }
}