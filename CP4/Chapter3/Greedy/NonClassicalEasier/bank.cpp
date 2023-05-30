#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, T, c, t; cin >> N >> T;
    int time = T;
    long long ans = 0;
    auto cmp = [](auto& p1, auto& p2) {
        if (p1.second == p2.second) return p1.first < p2.first;
        return p1.second < p2.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < N; i++) {
        cin >> c >> t;
        pq.emplace(c, t);
    }
    while (!pq.empty() && time >= 0) {
        pair<int, int> p = pq.top();
        pq.pop();
        if (p.second > time) {
            pq.emplace(p.first, p.second - 1);
        } else {
            time = min(p.second - 1, time - 1);
            ans += p.first;
        }
    }
    cout << ans;
}