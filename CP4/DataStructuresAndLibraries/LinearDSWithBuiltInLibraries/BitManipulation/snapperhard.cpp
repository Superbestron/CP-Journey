#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        int max = static_cast<int>(pow(2, n));
        bool on = k % max == (max - 1);
        cout << "Case #" << i << ": ";
        if (on) cout << "ON";
        else cout << "OFF";
        cout << endl;
    }
}