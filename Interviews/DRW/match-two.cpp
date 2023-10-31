#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;
typedef vector<int> vi;

int M = 0, N;
const int INF = 1e9;

inline int convertToV(int h, int c) {
    return h * N + c;
}

inline pair<int, int> convertToCoords(int v) {
    if (v == 0) {
        return {0, 0};
    }
    return {v / N, v % N};
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("execute with input file name as a command-line argument:\n"
               "e.g. ./a.out sample-input.txt\n");
        return 1;
    }

    printf("input file name is %s\n", argv[1]);

    // write your code to complete this program
    // 1. parse the input file
    // 2. figure out if this input is solvable
    // 3. write the required here_comes_santa_claus_validation_output.txt to stdout

    ifstream file(argv[1]);
    vector<string> v;
    string str;
    unordered_map<char, vi> mp;

    while (std::getline(file, str)) {
        N = str.size();
        for (int i = 0; i < N; i++) {
            if (str[i] != '.') {
                mp[str[i]].push_back(convertToV(M, i));
            }
        }
        M++;
        v.push_back(std::move(str));
    }
    int V = M * N;

    // i -> node, j -> direction reached
    typedef tuple<int, int, int> iii;
    priority_queue<iii, vector<iii>, greater<iii>> pq;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    map<tuple<char, int, int>, int> ans;
    for (int i = 0; i < V; i++) {
        auto [row, col] = convertToCoords(i);
        if (v[row][col] == '.') continue;
        vector<vector<int>> dist(V, vector<int>(4, INF));
        dist[i][0] = 0;
        dist[i][1] = 0;
        dist[i][2] = 0;
        dist[i][3] = 0;
        pq.emplace(0, i, 0);
        pq.emplace(0, i, 1);
        pq.emplace(0, i, 2);
        pq.emplace(0, i, 3);
        while (!pq.empty()) { // main loop
            auto [d, u, direc] = pq.top(); pq.pop(); // shortest unvisited u
            if (d > dist[u][direc]) continue; // a very important check
            for (int k = 0; k < 4; k++) {
                auto& direction = directions[k];
                auto [row, col] = convertToCoords(u);
                int new_x = row + direction[0];
                int new_y = col + direction[1];
                if (new_x < 0 || new_x == M || new_y < 0 || new_y == N) continue;
                if (dist[u][direc] + ((k == direc) ? 0 : 1) >= dist[convertToV(new_x, new_y)][k]) continue;
                dist[convertToV(new_x, new_y)][k] = dist[u][direc] + ((k == direc) ? 0 : 1);
                if (v[new_x][new_y] != '.') continue;
                pq.emplace(dist[convertToV(new_x, new_y)][k], convertToV(new_x, new_y), k);
            }
        }
        for (int dest : mp[v[row][col]]) {
            if (i == dest) continue;
            // Can match 'a' at (Row 0, Col 0) and (Row 1, Col 1) with 1 turns
            auto p = make_tuple(v[row][col], min(i, dest), max(i, dest));
            if (ans.count(p)) continue;
            int min_cost = INT32_MAX;
            for (int j = 0; j < 4; j++) {
                min_cost = min(min_cost, dist[dest][j]);
            }
            ans[p] = min_cost;
        }
    }
    // Can match 'a' at (Row 0, Col 0) and (Row 1, Col 1)
    for (auto& p : ans) {
        auto [src_r, src_c] = convertToCoords(get<1>(p.first));
        auto [dest_r, dest_c] = convertToCoords(get<2>(p.first));
        if (p.second == 1e9) continue;
        printf("Can match '%c' at (Row %d, Col %d) and (Row %d, Col %d) with %d turns\n",
               get<0>(p.first), src_r, src_c, dest_r, dest_c, p.second);
    }

    file.close();

    return 0;
}
