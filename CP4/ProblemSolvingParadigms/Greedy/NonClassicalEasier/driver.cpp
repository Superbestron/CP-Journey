#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> C(N), min_road_cost_so_far(N), T(N);
    min_road_cost_so_far[0] = INT32_MAX;
    for (int i = 1; i <= N - 1; i++) {
        cin >> C[i];
        min_road_cost_so_far[i] = min(min_road_cost_so_far[i - 1], C[i]);
    }
    for (int i = 0; i < N; i++) cin >> T[i];
    long long gate = 1, curr_time = 0, curr_cost = 0;
    while (gate < N) {
        // go to gate first;
        curr_time++;
        curr_cost += C[gate];
        // make extra trips
        long long time_left = T[gate] - curr_time;
        if (time_left > 0) {
            long long trips = time_left / 2 + time_left % 2;
            curr_time += 2 * trips;
            curr_cost += 2 * min_road_cost_so_far[gate] * trips;
        }
        gate++;
    }
    cout << curr_cost;
}