#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, temp, ans = 0; cin >> n >> m;
    priority_queue<int, vector<int>> task, interval;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        task.push(temp);
    }
    for (int i = 0; i < m; i++) {
        cin >> temp;
        interval.push(temp);
    }
    while (!interval.empty()) {
        int curr_interval = interval.top();
        interval.pop();
        while (!task.empty()) {
            int curr_task = task.top();
            task.pop();
            if (curr_task <= curr_interval) {
                ans++;
                break;
            }
        }
    }
    cout << ans;
}