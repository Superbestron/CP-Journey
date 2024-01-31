#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef tuple<int, int, int, int> iiii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k, temp;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<tuple<int, int>> arr;
        set<int> rows_not_used, cols_not_used;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            temp--;
            arr.emplace_back(temp, i);
            rows_not_used.insert(i);
            cols_not_used.insert(i);
        }
        sort(arr.begin(), arr.end());
        vector<iiii> v;
        for (int i = 0; i < k; i++) {
            v.emplace_back(n, -1, n, -1);
        }
        for (int i = 0; i < n; i++) {
            auto& [val, idx] = arr[i];
            auto& [minR, maxR, minC, maxC] = v[val];
            minR = min(minR, *rows_not_used.begin());
            maxR = max(maxR, *(rows_not_used.rbegin()));
            minC = min(minC, *cols_not_used.begin());
            maxC = max(maxC, *(cols_not_used.rbegin()));
            rows_not_used.erase(idx);
            cols_not_used.erase(idx);
        }
        for (int i = 0; i < k; i++) {
            auto& [minR, maxR, minC, maxC] = v[i];
            if (minR == n) cout << 0 << ' ';
            else cout << (maxR - minR + 1) + (maxC - minC + 1) << ' ';
        }
        cout << '\n';
    }
}

