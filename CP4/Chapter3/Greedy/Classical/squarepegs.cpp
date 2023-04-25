#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K, temp, ans = 0; cin >> N >> M >> K;
    priority_queue<double> plots, houses;
    while (N--) {
        cin >> temp;
        plots.push(temp);
    }
    while (M--) {
        cin >> temp;
        houses.push(temp);
    }
    while (K--) {
        cin >> temp;
        houses.push(sqrt((temp * temp) / 2.0));
    }
    while (!plots.empty()) {
        double curr_plot = plots.top();
        plots.pop();
        while (!houses.empty()) {
            double curr_house = houses.top();
            houses.pop();
            if (curr_house < curr_plot) {
                ans++;
                break;
            }
        }
    }
    cout << ans;
}