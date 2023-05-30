#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))

using namespace std;

int n, ans;
bool printed = false;
string best_str;
vector<string> v;
vector<int> best;
vector<bool> used(12);
unordered_map<int, unordered_set<int>> al;

void backtrack(int prev_colour, int size) {
    if (size == n) {
        if (!printed) {
            for (int i : best) best_str += v[i] + ' ';
            printed = true;
        }
        ans++;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (prev_colour == -1 || al[prev_colour].count(i) == 0) {
            used[i] = true;
            best.push_back(i);
            backtrack(i, size + 1);
            best.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t, m;
    string temp, temp2;
    cin >> t;
    while (t-- > 0) {
        cin >> n;
        ans = 0;
        v.clear();
        best.clear();
        al.clear();
        best_str.clear();
        printed = false;
        unordered_map<string, int> str_to_idx;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            v.push_back(temp);
            str_to_idx[temp] = i;
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> temp >> temp2;
            al[str_to_idx[temp]].insert(str_to_idx[temp2]);
            al[str_to_idx[temp2]].insert(str_to_idx[temp]);
        }

        backtrack(-1, 0);
        cout << ans << '\n';
        cout << best_str << '\n';
    }
}
