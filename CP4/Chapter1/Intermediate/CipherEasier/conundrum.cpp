#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    char arr[3] = {'P', 'E', 'R'};
    string s; cin >> s;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != arr[i % 3]) ans++;
    }
    cout << ans;
}