#include <bits/stdc++.h>

using namespace std;

// use greedy approach on 1 lab first before switching to another

int T, n, m, lab, a, b;
unordered_map<int, unordered_set<int>> AL;
queue<int> pq1, pq2;
bool is_lab_1[100001];
int in_degree[100001], temp_in_degree[100001];

int start_from_lab_1(bool curr_lab_1) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        in_degree[i] = temp_in_degree[i];
        if (in_degree[i] == 0) {
            if (is_lab_1[i]) pq1.push(i);
            else pq2.push(i);
        }
    }
    if (pq1.empty()) curr_lab_1 = false;
    queue<int>* pq = curr_lab_1 ? &pq1 : &pq2;
    while (true) {
        if (pq1.empty() && pq2.empty()) break;
        if (pq->empty()) {
            curr_lab_1 = !curr_lab_1;
            pq = curr_lab_1 ? &pq1 : &pq2;
            ans++;
        }
        int u = pq->front();
        pq->pop();
        for (int v : AL[u]) {
            --in_degree[v];
            if (in_degree[v] == 0) {
                if (is_lab_1[v]) pq1.push(v);
                else pq2.push(v);
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> lab;
            is_lab_1[i] = lab == 1;
        }
        memset(temp_in_degree, 0, sizeof temp_in_degree);
        AL.clear();
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            AL[a].insert(b);
            temp_in_degree[b]++;
        }
        cout << min(start_from_lab_1(true), start_from_lab_1(false)) << '\n';
    }
}
