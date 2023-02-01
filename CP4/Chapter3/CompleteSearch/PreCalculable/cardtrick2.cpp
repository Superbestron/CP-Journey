#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, n; cin >> T;
    while (T--) {
        cin >> n;
        queue<int> q;
        int ans[n], ctr = 1;
        for (int i = 1; i <= n; i++) q.push(i);
        while (ctr < n) {
            for (int i = 0; i < ctr; i++) {
                q.push(q.front());
                q.pop();
            }
            ans[q.front() - 1] = ctr;
            q.pop();
            ctr++;
        }
        ans[q.front() - 1] = ctr;
        for (int i = 0; i < n; i++) cout << ans[i] << ' ';
        cout << '\n';
    }
}
