#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<int> a(n), h(n);
        for (int& i : a) cin >> i;
        for (int& i : h) cin >> i;
        long long curr = 0, curr_len = 0, max_len = 0;
        queue<long long> q;
        for (int i = 0; i < n; i++) {
            long long val = a[i];
            if (curr != 0 && h[i - 1] % h[i] != 0) { // can't divide
                while (!q.empty()) q.pop();
                if (val > k) { // cannot add current val
                    curr = 0;
                    curr_len = 0;
                    continue;
                }
                q.push(val);
                curr = val;
                curr_len = 1;
            } else if (curr + val > k) {
                while (!q.empty()) {
                    curr -= q.front();
                    curr_len--;
                    q.pop();
                    if (curr + val <= k) break;
                }
                if (curr + val <= k) {
                    q.push(val);
                    curr += val;
                    curr_len++;
                }
            } else {
                q.push(val);
                curr += val;
                curr_len++;
            }
            max_len = max(max_len, curr_len);
        }
        cout << max_len << '\n';
    }
}