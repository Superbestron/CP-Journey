#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Simple Application of BFS

// up right down left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vii bytes;
    int n = 71, idx = 0;
    vector<string> grid(n, string(n, '.'));
    while (cin >> s) {
        vector<string> v = split(s, ',');
        bytes.emplace_back(stoi(v[0]), stoi(v[1]));
        if (idx < 1024) {
            grid[stoi(v[0])][stoi(v[1])] = '#';
            idx++;
        }
    }
    vector<vi> dist(n, vi(n, -1));
    dist[0][0] = 0;
    queue<ii> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto & dir : dirs) {
            int new_x = x + dir[0];
            int new_y = y + dir[1];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= n) continue;
            if (grid[new_x][new_y] == '#' || dist[new_x][new_y] >= 0) continue;
            dist[new_x][new_y] = dist[x][y] + 1;
            q.emplace(new_x, new_y);
        }
    }
    cout << dist[n - 1][n - 1] << '\n';
}
