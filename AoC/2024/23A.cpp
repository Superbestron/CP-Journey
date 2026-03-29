#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Implement as it is.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ans = 0;
    string s;
    unordered_map<string, unordered_set<string>> AL;
    unordered_set<string> nodes;
    while (cin >> s) {
        vector<string> vec = split(s, '-');
        const string& u = vec[0];
        const string& v = vec[1];
        AL[u].insert(v);
        AL[v].insert(u);
        nodes.insert(u);
        nodes.insert(v);
    }
    vector nodes_vec(nodes.begin(), nodes.end());
    for (int i = 0; i < nodes_vec.size(); i++) {
        const string& n1 = nodes_vec[i];
        bool n1_t = n1[0] == 't';
        for (int j = i + 1; j < nodes_vec.size(); j++) {
            const string& n2 = nodes_vec[j];
            bool n2_t = n2[0] == 't';
            if (!AL[n1].contains(n2)) continue;
            for (int k = j + 1; k < nodes_vec.size(); k++) {
                const string& n3 = nodes_vec[k];
                bool n3_t = n3[0] == 't';
                if (!n1_t && !n2_t && !n3_t) continue;
                if (!AL[n1].contains(n3)) continue;
                if (!AL[n2].contains(n3)) continue;
                ans++;
            }
        }
    }
    cout << ans << '\n';
}
