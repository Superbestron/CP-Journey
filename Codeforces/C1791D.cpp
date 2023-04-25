#include <bits/stdc++.h>

using namespace std;

int solve(string& s) {
    vector<int> top(26), bot(26);
    for (char &c : s) {
        top[c - 'a']++;
    }
    int ans = 0;
    for (char &c : s) {
        bot[c - 'a']++;
        top[c - 'a']--;
        int score = 0;
        for (int i = 0; i < 26; i++) {
            if (top[i] > 0) score++;
            if (bot[i] > 0) score++;
        }
        ans = max(ans, score);
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    string s;
    while (t--) {
        cin >> n >> s;
        cout << solve(s) << '\n';
    }
}
