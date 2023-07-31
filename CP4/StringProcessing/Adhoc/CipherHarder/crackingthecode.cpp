#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        string M[n], D, X;
        unordered_map<char, char> best;
        bool has_sub = false;
        for (int i = 0; i < n; i++) cin >> M[i];
        cin >> D >> X;
        for (int i = 0; i < n; i++) {
            if (M[i].size() != D.size()) continue;
            unordered_map<char, char> curr;
            unordered_set<char> used;
            bool can = true;
            for (int j = 0; j < D.size(); j++) {
                // Char map to 2 diff
                if (curr.count(M[i][j])) {
                    if (curr[M[i][j]] != D[j]) {
                        can = false;
                        break;
                    }
                // 2 char map to same char
                } else if (used.count(D[j])) {
                    can = false;
                    break;
                } else {
                    curr[M[i][j]] = D[j];
                    used.insert(D[j]);
                }
            }
            if (can) {
                if (!has_sub) {
                    best = std::move(curr);
                    has_sub = true;
                }
                else {
                    unordered_map<char, char> merged;
                    for (auto& [k, v] : best) {
                        if (curr.count(k) && best[k] == curr[k]) {
                            merged[k] = best[k];
                        }
                    }
                    best = std::move(merged);
                }
            }
        }
        string ans;
        unordered_set<char> alphabet1, alphabet2;
        // EDGE CASE BEWARE, you can deduce the last char mapping
        if (best.size() == 25) {
            for (char c = 'a'; c <= 'z'; c++) {
                alphabet1.insert(c);
                alphabet2.insert(c);
            }
            for (auto& [k, v] : best) {
                alphabet1.erase(k);
                alphabet2.erase(v);
            }
            best[*alphabet1.begin()] = *alphabet2.begin();
        }
        for (char c : X) {
            if (best.count(c)) {
                ans += best[c];
            }
            else ans += '?';
        }
        if (!has_sub) cout << "IMPOSSIBLE\n";
        else cout << ans << '\n';
    }
}