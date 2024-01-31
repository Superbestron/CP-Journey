#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, h; cin >> t;
    while (t--) {
        cin >> n;
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            cin >> h;
            pq.push(h);
        }
        int ans = 0;
        while (!pq.empty()) {
            int curr = pq.top();
            if (pq.size() == 1) pq.pop();
            else if (curr > 2) {
                pq.pop();
            } else {
                int first = pq.top(); pq.pop();
                int second = pq.top(); pq.pop();
                if (first - 1 > 0) pq.push(first - 1);
                if (second - 1 > 0) pq.push(second - 1);
            }
            ans++;
        }
        cout << ans << '\n';
    }
}
