#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s;
    while (n--) {
        cin >> s;
        int freq[26], cnt = 0;
        memset(freq, 0, sizeof freq);
        for (char c : s) freq[c - 'a']++;
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                cnt++;
            }
        }
        if (cnt > 1) cout << "Impossible\n";
        else {
            int ans = 0;
            for (int i = 0; i < s.size() / 2; i++) {
                char c = s[i];
                int idx = -1;
                for (int j = s.size() - 1 - i; j > i; j--) {
                    if (s[j] == c) {
                        idx = j; break;
                    }
                }
                if (idx == -1) {
                    swap(s[i], s[i + 1]);
                    ans++;
                    i--;
                    continue;
                }
                for (int j = idx; j < s.size() - 1 - i; j++) {
                    swap(s[j], s[j + 1]);
                    ans++;
                }
            }
            cout << ans << '\n';
        }
    }
}