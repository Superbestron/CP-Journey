#include <iostream>
#include <vector>

using namespace std;

int dfs(int node, int* visited, vector<vector<int>>& al) {
    if (visited[node] != 0) {
        return visited[node];
    }
    int ans = 1;
    for (auto i : al[node]) {
        ans += dfs(i, visited, al);
    }
    visited[node] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T,A,N,start,end;
    cin>>T;
    for (int t = 1; t <= T; t++) {
        cin>>N;
        vector<int> capacities;
        vector<vector<int>> al;
        for (int k = 0; k < N; k++) {
            cin>>A;
            capacities.push_back(A);
            al.emplace_back(vector<int>());
        }
        for (int k = 0; k < N - 1; k++) {
            cin>>start>>end;
            int startC = capacities[start - 1];
            int endC = capacities[end - 1];
            if (startC < endC) {
                al[end-1].push_back(start-1);
                //cout<<al[end-1]<<endl;
            } else if (endC < startC) {
                al[start-1].push_back(end-1);
            }
        }

        int visited[N];
        int ans = 0;
        fill(visited, visited + N, 0);
        for (int k = 0; k < N; k++) {
            // not visited
            if (visited[k] == 0) {
                // do dfs
                ans = max(ans, dfs(k, visited, al));
            }
        }

        cout << "Case #" << t << ": " << ans << '\n';
    }
}

