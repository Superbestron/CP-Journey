#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // energy : gold reward
    map<int, priority_queue<int>, greater<>> m;
    int n, e, g, x; cin >> n;
    string command;
    while (n--) {
        long long gold = 0; // impt
        cin >> command;
        if (command[0] == 'a') {
            cin >> e >> g;
            m[e].push(g);
        } else {
            cin >> x;
            for (auto it = m.lower_bound(x); it != m.end();) {
                priority_queue<int>& pq = it->second;
                while (!pq.empty()) {
                    if (x >= it->first) {
                        gold += pq.top();
                        x -= it->first;
                        pq.pop();
                    } else break;
                }
                if (pq.empty()) it = m.erase(it);
                else it = m.lower_bound(x);
            }
            cout << gold << endl;
        }
    }
}