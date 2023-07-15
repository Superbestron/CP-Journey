#include <bits/stdc++.h>

using namespace std;

// Key idea is to simulate the painting backwards. We know that we always want to "segregate" the biggest consecutive
// segments of paintings first so that we paint them as little times as possible. This means that the smallest segments
// of paintings are painted last. So we greedily combine the two smallest segments to form a larger one, till we are
// left with 2 segments.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, N, s; cin >> T;
    while (T--) {
        priority_queue<long long, vector<long long>, greater<>> pq;
        cin >> N;
        long long ans = 0;
        for (int i = 0; i < N; i++) {
            cin >> s;
            pq.push(s);
        }
        while (pq.size() >= 2) {
            long long sum = 0;
            sum += pq.top(); pq.pop();
            sum += pq.top(); pq.pop();
            pq.push(sum);
            ans += sum;
        }
        cout << ans << '\n';
    }
}