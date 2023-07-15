#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, L, U, ans = 0; cin >> N;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    while (N--) {
        cin >> L >> U;
        pq.emplace(L, U);
    }
    while (!pq.empty()) {
        pair<int, int> minion = pq.top();
        pq.pop(); ans++;
        // greedily set the room to the upper limit
        int new_room_upper = minion.second;
        while (!pq.empty()) {
            pair<int, int> other_minion = pq.top();
            // means can fit into current room
            if (other_minion.first > new_room_upper) break;
            pq.pop();
            new_room_upper = min(new_room_upper, other_minion.second);
        }
    }
    cout << ans;
}