#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, a, b;
    cin >> t;
    auto cmp = [](auto& p1, auto& p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first > p2.first;
    };
    while (t--) {
        cin >> n;
        priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);
        priority_queue<pi, vector<pi>, decltype(cmp)> taken(cmp);
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            pq.emplace(a, b);
        }
        long long ctr = 0, pts = 0;
        while (!pq.empty()) {
            auto curr = pq.top(); pq.pop();
            taken.emplace(curr);
            ctr++;
            pts += curr.second;
            int blown = 0;
            while (!taken.empty()) {
                auto next = taken.top();
                if (next.first > ctr) {
                    break;
                }
                blown++; taken.pop();
            }
            while (!pq.empty()) {
                auto next = pq.top();
                if (next.first > ctr) {
                    break;
                }
                pq.pop();
            }
            ctr -= blown;
        }
        cout << pts << '\n';
    }
}