#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> v(n), ans;
    for (int i = 0; i < n; i++) cin >> v[i];
    deque<pair<int, int>> min_window, max_window; // we maintain min_window to be sorted in ascending/descending order
    for (int i = 0; i < n; i++) { // this is O(n)
        while (!min_window.empty() && min_window.back().first >= v[i]) min_window.pop_back();
        min_window.emplace_back(v[i], i); // keep min_window ordered
        // use the second field to see if this is part of the current min_window
        while (min_window.front().second <= i - m) min_window.pop_front(); // lazy deletion

        while (!max_window.empty() && max_window.back().first <= v[i]) max_window.pop_back();
        max_window.emplace_back(v[i], i); // keep max_window ordered
        // use the second field to see if this is part of the current max_window
        while (max_window.front().second <= i - m) max_window.pop_front(); // lazy deletion
        if (i + 1 >= m) {
            int diff = max_window.front().first - min_window.front().first;
            if (diff <= c) ans.push_back(i - m + 2);
        }
    }
    if (ans.empty()) cout << "NONE\n";
    else for (int i : ans) cout << i << '\n';
}