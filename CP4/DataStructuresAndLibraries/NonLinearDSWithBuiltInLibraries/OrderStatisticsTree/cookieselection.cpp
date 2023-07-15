#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string symbol;
    int n, m, t, p; cin >> n >> m;
    auto cmp = [](auto& p1, auto& p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first > p2.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    while (m--) {
        cin >> t >> p;
        pq.emplace(t, p);
        cout << pq.top().first << '\n';
    }
}
