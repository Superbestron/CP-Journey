#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
vector<tuple<int, int, double>> v;
int x, y, n, l, u;
double f;

bool can(double speed) {
    double total_speed_up_time = 0, total_x_dist = 0;
    for (auto& tup : v) {
        total_speed_up_time += get<1>(tup) - get<0>(tup);
        total_x_dist += speed * (get<1>(tup) - get<0>(tup)) * get<2>(tup);
    }
    total_x_dist += (y - total_speed_up_time) * speed;
    return total_x_dist >= abs(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> x >> y >> n;
    for (int i = 0; i < n; i++) {
        cin >> l >> u >> f;
        v.emplace_back(l, u, f);
    }
    double lo = 0, hi = abs(x);
    while (fabs(hi - lo) > EPS) {
        double mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid;
    }
    cout << fixed << setprecision(10) << (x < 0 ? -hi : hi);
}