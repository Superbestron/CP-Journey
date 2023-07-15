#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, s, ans = 0;
    cin >> n >> m;
    // finish : lock
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        cin >> a >> s;
        v.emplace_back(a,s);
    }
    sort(v.begin(),v.end());
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        a = v[i].first;
        s = v[i].second;
        while (!pq.empty()) {
            // all available machines are full
            if (-pq.top() > a) break;
            // current machine can be used (unlocked)
            if (-pq.top() + m >= a) {
                ans++;
                pq.pop();
                break;
            }
            pq.pop();
        }

        pq.push(- (a + s));
    }
    cout << ans;
}

