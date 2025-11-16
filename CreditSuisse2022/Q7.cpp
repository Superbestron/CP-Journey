#include <bits/stdc++.h>
#define GRAY 1
#define WHITE 0
using namespace std;

bool dfs(int visited[], vector<vector<pair<int, int>>>& al, int node, int prevWeight) {
    visited[node] = GRAY;
    for (auto& edge : al[node]) {
        if (prevWeight > edge.second) {
            if (visited[edge.first] == GRAY) {
                return true;
            }
            continue;
        }
        if (visited[edge.first] == GRAY) {
            return true;
        } else if (visited[edge.first] == WHITE) {
            if (dfs(visited, al, edge.first, edge.second)) {
                return true;
            }
        }
    }
    visited[node] = WHITE;
    return false;
}

bool solution(int n, int l, const vector<vector<int>>& transfers) {
    vector<vector<pair<int, int>>> al;
    for (int i = 0; i < n; i++)  {
        al.emplace_back(vector<pair<int, int>>());
    }
    for (int i = 0; i < l; i++) {
        int from = transfers[i][0];
        int to = transfers[i][1];
        if (from == to) continue;
        al[from].push_back({to, i});
    }

    bool ans = false;
    int visited[n];
    fill(visited, visited + n, WHITE);
    for (int i = 0; i < n; i++) {
        if (visited[i] == WHITE) {
            ans = dfs(visited, al, i, -1);
            if (ans) {
                return true;
            }
        }
    }
    return ans;
}

int main() {
    int n, l;
    cin >> n >> l;

    vector<vector<int>> transfers;
    vector<int> transfer(2);
    for (int i = 0; i < l; i++) {
        cin >> transfer[0] >> transfer[1];
        transfers.push_back(transfer);
    }

    bool result = solution(n, l, transfers);
    result ? cout << "Ineligible\n" : cout << "Eligible\n";
}
