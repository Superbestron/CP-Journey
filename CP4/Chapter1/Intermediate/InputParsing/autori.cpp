#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, ans; cin >> s;
    for (char c : s) {
        if (isupper(c)) ans += c;
    }
    cout << ans;
}