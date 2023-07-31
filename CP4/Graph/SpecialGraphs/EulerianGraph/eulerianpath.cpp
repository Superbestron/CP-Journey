#include <bits/stdc++.h>

using namespace std;

vector<int> in_deg, out_deg;
vector<vector<int>> AL;
int n, m, a, b;

vector<int> hierholzer(int x) {
    vector<int> ans, idx(n, 0), st;
    st.push_back(x);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)AL[u].size()) {            // still has neighbor
            st.push_back(AL[u][idx[u]]);
            ++idx[u];
        }
        else {
            ans.push_back(u);
            st.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m && !(m == 0 && n == 0)) {
        AL.assign(n, {});
        in_deg.assign(n, 0);
        out_deg.assign(n, 0);
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            AL[a].push_back(b);
            in_deg[b]++;
            out_deg[a]++;
        }
        vector<int> ans;
        int potential_start = 0, potential_end = 0, equal_in_out = 0;
        int start_node = 0;
        for (int i = 0; i < n; i++) {
            if (in_deg[i] + 1 == out_deg[i]) {
                potential_start++;
                start_node = i;
            }
            if (in_deg[i] == out_deg[i] + 1) {
                potential_end++;
            }
            if (in_deg[i] == out_deg[i]) {
                equal_in_out++;
            }
        }
        if (equal_in_out == n) {  // eulerian cycle present
            ans = hierholzer(start_node);
        } else if (potential_start == 1 && potential_end == 1 && equal_in_out == n - 2) {  // eulerian path present
            ans = hierholzer(start_node);
        }
        if (ans.size() <= m) cout << "Impossible";
        else for (int i : ans) cout << i << ' ';
        cout << '\n';
    }
}