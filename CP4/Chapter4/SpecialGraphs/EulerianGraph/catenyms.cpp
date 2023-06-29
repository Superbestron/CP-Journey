#include <bits/stdc++.h>

using namespace std;

vector<char> arr;
set<string> strings;
vector<int> in_deg, out_deg;
vector<vector<int>> AL;

vector<int> hierholzer(int x) {
    vector<int> ans, idx(26, 0), st;
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
    int t, n;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string str;
    cin >> t;
    for (char c = 'a'; c <= 'z'; c++) {
        arr.push_back(c);
    }
    while (t--) {
        cin >> n;
        AL.assign(26, {});
        strings.clear();
        in_deg.assign(26, 0);
        out_deg.assign(26, 0);
        for (int i = 0; i < n; i++) {
            cin >> str;
            strings.insert(str);
        }
        for (auto& string : strings) {
            AL[string.front() - 'a'].push_back(string.back() - 'a');
            in_deg[string.back() - 'a']++;
            out_deg[string.front() - 'a']++;
        }

        vector<int> ans;
        int potential_start = 0, potential_end = 0, equal_in_out = 0;
        int start_node = 0, equal_node = -1;
        for (int i = 0; i < 26; i++) {
            if (in_deg[i] + 1 == out_deg[i]) {
                potential_start++;
                start_node = i;
            }
            if (in_deg[i] == out_deg[i] + 1) {
                potential_end++;
            }
            if (in_deg[i] == out_deg[i]) {
                equal_in_out++;
                // to know which node is part of the cycle
                if (in_deg[i] > 0 && equal_node == -1) {  // start from the earliest possible node
                    equal_node = i;
                }
            }
        }
        if (equal_in_out == 26) {  // eulerian cycle present
            ans = hierholzer(equal_node);
        } else if (potential_start == 1 && potential_end == 1 && equal_in_out == 24) {  // eulerian path present
            ans = hierholzer(start_node);
        }
        string output_str;
        for (int i = 0; i < (int) ans.size() - 1; i++) {
            string st;
            st += static_cast<char>(ans[i] + 'a');
            char last_char = static_cast<char>(ans[i + 1] + 'a');
            auto it = strings.lower_bound(st);
            while (it->back() != last_char) {
                it++;
            }
            output_str += *it;
            output_str += '.';
            strings.erase(it);
        }
        output_str.pop_back();
        if (ans.size() <= n) cout << "***";
        else cout << output_str;
        cout << "\n";
    }
}