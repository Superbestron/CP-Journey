#include <bits/stdc++.h>

using namespace std;

// Check out prufer sequence

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n - 1), degree(n + 2, 1), ans;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        degree[a[i]]++;
    }
    for (int i = 1; i < n + 2; i++) {
        if (degree[i] == 1) pq.push(i);
    }
    for (int i = 0; i < n - 1; i++) {
        int node = pq.top(); pq.pop();
        if (degree[node] == 1) {
            degree[a[i]]--;
            if (degree[a[i]] == 1) pq.push(a[i]);
            degree[node]--;
            ans.push_back(node);
        }
    }

    int u = pq.top(); pq.pop();
    int v = pq.top();
    cin >> a[n - 1];
    if (a[n - 1] == v) {
        ans.push_back(u);
        for (int i : ans) cout << i << '\n';
    } else cout << "Error";
}
