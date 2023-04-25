#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, M; cin >> n;
    while (n--) {
        string s, ans;
        cin >> s;
        int root = floor(sqrt(s.size()));
        if (s.size() == root * root) {
            M = s.size();
        } else {
            M = (root + 1) * (root + 1);
        }
        for (int i = s.size(); i < M; i++) s += '*';
        for (int i = s.size() - sqrt(M); i < M; i++) {
            for (int j = i; j >= 0; j -= sqrt(M)) {
                if (s[j] != '*') ans += s[j];
            }
        }
        cout << ans << '\n';
    }
}