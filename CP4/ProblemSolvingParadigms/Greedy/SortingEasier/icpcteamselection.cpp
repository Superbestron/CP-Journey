#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, N, val; cin >> t;
    while (t--) {
        cin >> N;
        priority_queue<int> pq;
        int ans = 0;
        for (int i = 0; i < 3 * N; i++) {
            cin >> val;
            pq.push(val);
        }
        for (int i = 0; i < 2 * N; i++) {
            val = pq.top();
            pq.pop();
            if (i % 2) {
                ans += val;
            }
        }
        cout << ans << '\n';
    }
}