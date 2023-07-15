#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    double T, w, mini = MAXFLOAT;
    int N, ans = 0; cin >> T >> N;
    priority_queue<double> pq;
    while (N--) {
        cin >> w;
        pq.push(w);
        mini = min(mini, w * 1.0);
    }
    while (mini / pq.top() <= T) {
        double cut_piece = pq.top() / 2;
        pq.pop();
        pq.push(cut_piece); pq.push(cut_piece);
        mini = min(cut_piece, mini);
        ans++;
    }
    cout << ans;
}