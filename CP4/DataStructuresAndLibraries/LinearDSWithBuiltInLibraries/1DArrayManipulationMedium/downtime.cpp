#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, k, c, ans = 1;
    cin >> n >> k;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < k; i++) {
        pq.push(0);
    }
    while (n-- > 0) {
        cin >> c;
        int avai = pq.top();
        if (avai <= c) {
            pq.pop();
        } else {
            ans++;
            // account for 1 added below
            for (int i = 0; i < k - 1; i++) {
                pq.push(0);
            }
        }
        pq.push(c + 1000);
    }
    cout << ans;
}