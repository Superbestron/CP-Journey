#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, n, val; cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> n;
        long long ans = 0;
        priority_queue<long long> v1;
        priority_queue<long long, vector<long long>, greater<>> v2;
        for (int j = 0; j < n; j++) {
            cin >> val;
            v1.push(val);
        }
        for (int j = 0; j < n; j++) {
            cin >> val;
            v2.push(val);
        }
        while (!v1.empty()) {
            ans += v1.top() * v2.top();
            v1.pop(); v2.pop();
        }
        cout << "Case #" << i << ": " << ans << '\n';
    }
}