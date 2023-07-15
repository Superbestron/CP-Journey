#include <bits/stdc++.h>

using namespace std;

// Problem is quite tricky. Refer to below example:
// 6
//  \
//  8
//  /
// 7
// In this case, 7 will need to be "connected" to 8 instead of 6. So we take the max height of 6 and 8 and +1.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val; cin >> n;
    long long ans = 0;
    set<int> s;
    vector<int> height(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> val;
        s.insert(val);
        auto left_it = s.find(val);
        auto right_it = left_it;

        int cost = 0;
        if (left_it != s.begin()) {
            left_it--;
            cost = height[*left_it];
        }

        if (right_it != --s.end()) {
            right_it++;
            cost = max(height[*right_it], cost);
        }

        ans += cost;
        height[val] = ++cost;
        cout << ans << endl;
    }
}
