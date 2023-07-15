#include <iostream>
#include <stack>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val, curr_max = 0, max_fall = 0;
    stack<pair<int, int>> s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        curr_max = max(curr_max, val);
        // if we have found a mountain higher than what is on the stack
        if (curr_max == val) {
            int first_idx = -1;
            int maxi = 0, mini = INT_MAX;
            while (!s.empty()) {
                mini = min(s.top().first, mini);
                maxi = max(s.top().first, maxi);
                first_idx = s.top().second;
                s.pop();
            }
            if (i - first_idx > 1) { // minimum must be 2 mountains apart for a bungee
                maxi = min(val, maxi); // highest point is the min height of the 2 end mountains
                max_fall = max(max_fall, maxi - mini);
            }
        }
        s.emplace(val, i);
    }
    // cover cases where answer can be found on the stack
    int maxi = 0, mini = INT_MAX;
    while (!s.empty()) {
        if (s.top().first >= maxi) {
            if (mini != INT_MAX) max_fall = max(max_fall, maxi - mini); // ensure we find a min in between 2 mountains
            maxi = s.top().first;
            mini = INT_MAX;
        } else {
            mini = min(s.top().first, mini);
        }
        s.pop();
    }
    cout << max_fall << endl;
}