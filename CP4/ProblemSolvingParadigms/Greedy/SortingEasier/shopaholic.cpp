#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p; cin >> n;
    long long ans = 0;
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        cin >> p;
        pq.push(p);
    }
    while (pq.size() >= 3) {
        pq.pop(); pq.pop();
        ans += pq.top();
        pq.pop();
    }
    cout << ans;
}