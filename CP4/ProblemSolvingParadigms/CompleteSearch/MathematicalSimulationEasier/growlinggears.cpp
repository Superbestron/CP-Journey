#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    double a, b, c;
    while (t--) {
        cin >> n;
        double maxi = -99999;
        int gear = -1;
        for (int i = 1; i <= n; i++) {
            cin >> a >> b >> c;
            // differentiate the curve
            double r = b / 2 / a;
            double max_torque = r * r * -a + r * b + c;
            if (max_torque > maxi) {
                maxi = max_torque;
                gear = i;
            }
        }
        cout << gear << '\n';
    }
}