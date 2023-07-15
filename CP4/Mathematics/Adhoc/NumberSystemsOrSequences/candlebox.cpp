#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int D, R, T; cin >> D >> R >> T;
    int theo = 0;
    // brute force Theo's age
    for (; theo < 1000; theo++) {
        if ((theo + D) * (theo + D + 1) / 2 + theo * (theo + 1) / 2 - 9 == R + T) break;
    }
    int rita = theo + D;
    cout << R - (rita * (rita + 1) / 2 - 6);
}