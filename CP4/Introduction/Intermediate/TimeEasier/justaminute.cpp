#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, S, total_M = 0, total_S = 0; cin >> N;
    while (N--) {
        cin >> M >> S;
        total_M += M * 60;
        total_S += S;
    }
    double ans = static_cast<double>(total_S) / total_M;
    if (ans <= 1) cout << "measurement error";
    else cout << setprecision(9) << ans;
}