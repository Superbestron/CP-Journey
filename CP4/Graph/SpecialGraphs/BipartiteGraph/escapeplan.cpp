#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi match, vis;                                   // global variables
vector<pair<double, double>> robots, holes;
vector<vi> AL;
const double EPS = 1e-9;

int Aug(int L) {
    if (vis[L]) return 0;                          // L visited, return 0
    vis[L] = 1;
    for (auto &R : AL[L])
        if ((match[R] == -1) || Aug(match[R])) {
            match[R] = L;                              // flip status
            return 1;                                  // found 1 matching
        }
    return 0;                                      // no matching
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 1, N, M, time[3] = {5, 10, 20};
    double a, b;
    while (cin >> N && N != 0) {
        robots.clear();
        holes.clear();
        for (int i = 0; i < N; i++) {
            cin >> a >> b;
            robots.emplace_back(a, b);
        }
        cin >> M;
        for (int i = 0; i < M; i++)  {
            cin >> a >> b;
            holes.emplace_back(a, b);
        }
        printf("Scenario %d\n", tc);
        for (int i : time) {
            AL.assign(N + M, vector<int>());
            for (int j = 0; j < robots.size(); j++) {
                auto& robot = robots[j];
                for (int k = 0; k < holes.size(); k++) {
                    auto& hole = holes[k];
                    if (sqrt(pow(robot.first - hole.first, 2) + pow(robot.second - hole.second, 2)) - 10 * i < EPS) {
                        AL[j].push_back(k + N);
                    }
                }
            }
            match.assign(N + M, -1);
            int MCBM = 0;     // for each free vertex
            for (int j = 0; j < N; j++) {                        // (in random order)
                vis.assign(N + M, 0);                        // reset first
                MCBM += Aug(j);                              // try to match f
            }
            printf("In %d seconds %d robot(s) can escape\n", i, MCBM);
        }
        tc++;
        printf("\n");
    }
}