#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, min = 100000, ans, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        if (val < min) {
            min = val;
            ans = i;
        }
    }
    cout << ans;
}