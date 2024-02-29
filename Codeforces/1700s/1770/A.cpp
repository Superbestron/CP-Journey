#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m, temp; cin >> t;
    while (t--) {
        long long val = 0;
        cin >> n >> m;
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            pq.push(temp);
        }
        for (int i = 0 ; i < m; i++) {
            cin >> temp;
            pq.pop();
            pq.push(temp);
        }
        while (!pq.empty()) {
            val += pq.top(); pq.pop();
        }
        cout << val << endl;
    }
}