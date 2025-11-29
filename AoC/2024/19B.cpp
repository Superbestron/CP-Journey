#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Very minimal change from 19A; changing bool to ll.

unordered_map<char, vector<string>> mp;
unordered_map<string, ll> mp2;

bool check_string(string& sub, string& patt) {
    if (sub.size() < patt.size()) return false;
    for (int i = 0; i < patt.size(); i++) {
        if (sub[i] != patt[i]) return false;
    }
    return true;
}

ll dfs(string sub) {
    if (sub.empty()) return 1;
    if (mp2.count(sub)) return mp2[sub];
    char c = sub[0];
    ll ans = 0;
    for (auto& s : mp[c]) {
        if (!check_string(sub, s)) continue;
        ans += dfs(sub.substr(s.size(), sub.size() - s.size()));
    }
    return mp2[sub] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    bool front = true;
    ll ans = 0;
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
