#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
int a, d, h, t, total_time = 0, height = 0;
pair<int, int> elevation[5000], descent[5000];

bool can(double time) {
    double time_left_up = time, distance_up = 0;
    double time_left_down = time, distance_down = height;
    for (int i = 0; i < a; i++) {
        if (time_left_up <= elevation[i].second) {
            distance_up += time_left_up / elevation[i].second * elevation[i].first;
            break;
        }
        time_left_up -= elevation[i].second;
        distance_up += elevation[i].first;
    }
    for (int i = 0; i < d; i++) {
        if (time_left_down <= descent[i].second) {
            distance_down -= time_left_down / descent[i].second * descent[i].first;
            break;
        }
        time_left_down -= descent[i].second;
        distance_down -= descent[i].first;
    }
    return distance_up >= distance_down;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> d;
    for (int i = 0; i < a; i++) {
        cin >> h >> t;
        elevation[i] = make_pair(h, t);
        total_time += t;
        height += h;
    }
    for (int i = 0; i < d; i++) {
        cin >> h >> t;
        descent[i] = make_pair(h, t);
    }
    double lo = 0, hi = total_time;
    while (fabs(hi - lo) > EPS) {
        double mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid;
    }
    cout << fixed << setprecision(5) << hi;
}