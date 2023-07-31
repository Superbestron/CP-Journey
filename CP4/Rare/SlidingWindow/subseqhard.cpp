#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, N, V; cin >> T;
    while (T--) {
        cin >> N;
        int curr_sum = 0, ans = 0;
        queue<int> q;
        for (int i = 0; i < N; i++) {
            cin >> V;
            curr_sum += V;
            q.push(V);
            while (curr_sum > 47) {
                int curr = q.front(); q.pop();
                curr_sum -= curr;
            }
            if (curr_sum == 47) ans++;
            cout << curr_sum << '\n';
        }
        cout << ans << '\n';
    }
}