#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

int n, m, idx, ans;
vector<vector<int>> AL;
vector<unordered_set<int>> v;

void backtrack(int u, int size) {
    if (u == n) {
        ans = min(ans, size);
        return;
    }
    if (size >= ans) return;
    int to_insert = 0;
    while (!v[to_insert].empty()) {
        // check if can put in
        bool can = true;
        for (int o : AL[u]) {
            if (v[to_insert].count(o)) {
                can = false;
                break;
            }
        }
        if (can) {
            v[to_insert].insert(u);
            backtrack(u + 1, size);
            v[to_insert].erase(u);
        }
        to_insert++;
    }
    v[to_insert].insert(u);
    backtrack(u + 1, size + 1);
    v[to_insert].erase(u);
}

int main() {
    string a, b;
    while (cin >> n >> m && !(n == 0 && m == 0)) {
        unordered_map<string, int> name_to_int;
        idx = 0;
        ans = INT32_MAX;
        AL.assign(15, {});
        v.assign(15, unordered_set<int>());
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            if (!name_to_int.count(a)) {
                name_to_int[a] = idx++;
            }
            if (!name_to_int.count(b)) {
                name_to_int[b] = idx++;
            }
            int a_idx = name_to_int[a], b_idx = name_to_int[b];
            AL[a_idx].push_back(b_idx);
            AL[b_idx].push_back(a_idx);
        }
        backtrack(0, 0);
        cout << ans << '\n';
    }
}