#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string P, S; cin >> P >> S;
    unordered_map<char, int> s;
    for (char c : P) s[c]++;
    int p_idx = 0, s_idx = 0;
    while (p_idx < P.size()) {
        char c = P[p_idx];
        while (s_idx < S.size() && S[s_idx] != c) {
            if (s.count(S[s_idx])) {
                cout << "FAIL";
                return 0;
            }
            s_idx++;
        }
        if (s_idx == S.size()) {
            cout << "FAIL";
            return 0;
        }
        p_idx++;
        s_idx++;
        s[c]--;
        if (s[c] == 0) s.erase(c);
    }
    cout << "PASS";
}