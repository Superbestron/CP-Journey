#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m, k, a, b;
    cin >> n >> m >> k;
    vector<long long> spectators(n);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>> pq;
    vector<long long> freq(n + 1);
    for (int i = 0; i < n; i++) cin >> spectators[i];
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        freq[a - 1]++;
        freq[b]--;
    }
    long long running_sum = 0, total_sum = 0;
    for (int i = 0; i < n; i++) {
        running_sum += freq[i];
//        total_count += running_sum;
        freq[i] = running_sum;
        total_sum += running_sum * spectators[i];
        pq.emplace(running_sum, i);
    }
    while (!pq.empty() && k - spectators[pq.top().second] >= 0) {
        total_sum -= freq[pq.top().second] * spectators[pq.top().second];
        k -= spectators[pq.top().second];
        pq.pop();
    }
    if (k > 0 && !pq.empty()) {
        total_sum -= k * freq[pq.top().second];
    }
    cout << total_sum;
}