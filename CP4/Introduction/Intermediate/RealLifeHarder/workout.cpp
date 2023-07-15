#include <bits/stdc++.h>

using namespace std;

int j_u, j_r, u, r, t, curr_time = 0, steps = 0;
pair<int, int> jim[10];
tuple<int, int, int> machines[10];

int time_until_can_start(int index) {
    tuple<int, int, int>& machine = machines[index];
    // difference between curr_time and machine_start
    int x = curr_time - get<2>(machine);
    if (x < 0) {
        get<2>(machine) = max(get<2>(machine), curr_time + jim[index].first);
        return 0; // just start first
    }
    x %= (get<0>(machine) + get<1>(machine));
    // machine does first
    if (x < get<0>(machine)) {
        // see which is longer, other person's recovery vs jim's time to finish
        get<2>(machine) = max(jim[index].first + get<0>(machine) + curr_time - x,
                              get<0>(machine) + get<1>(machine) + curr_time - x);
        return get<0>(machine) - x;
    } else { // machine will finish first before jim can start
        get<2>(machine) =
                max(jim[index].first + curr_time, get<0>(machine) + get<1>(machine) + curr_time - x);
        return 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (auto& i : jim) {
        cin >> j_u >> j_r;
        i = make_pair(j_u, j_r);
    }
    for (auto& machine : machines) {
        cin >> u >> r >> t;
        machine = make_tuple(u, r, t);
    }
    while (steps < 30) {
        curr_time += time_until_can_start(steps % 10);
        curr_time += jim[steps % 10].first + jim[steps % 10].second;
        steps++;
    }

    curr_time -= jim[9].second;
    cout << curr_time;
}