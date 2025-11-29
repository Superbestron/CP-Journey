#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Simple recursive backtracking approach. Try every possible combination of strings to get the big string. This can be
// sped up with memoisation. I could have use std::string_view to avoid string copying in the map keys, but the
// suboptimal approach seems fast enough.

unordered_map<char, vector<string>> mp;
unordered_map<string, bool> mp2;

bool check_string(string& sub, string& patt) {
    if (sub.size() < patt.size()) return false;
    for (int i = 0; i < patt.size(); i++) {
        if (sub[i] != patt[i]) return false;
    }
    return true;
}

bool dfs(string sub) {
    if (sub.empty()) return true;
    if (mp2.count(sub)) return mp2[sub];
    char c = sub[0];
    bool ans = false;
    for (auto& s : mp[c]) {
        if (!check_string(sub, s)) continue;
        ans |= dfs(sub.substr(s.size(), sub.size() - s.size()));
    }
    return mp2[sub] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;

    bool front = true;
    int ans = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            front = false;
            continue;
        }
        if (front) {
            istringstream ss(s);
            while (ss >> t) {
                if (t.back() == ',') t.pop_back();
                mp[t.front()].push_back(t);
            }
        } else ans += dfs(s);
    }
    cout << ans << '\n';
}
