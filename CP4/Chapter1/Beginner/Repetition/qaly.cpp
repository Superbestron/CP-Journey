#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double ans = 0, t1, t2;
    cin >> n;
    while (n-- > 0) {
        cin >> t1 >> t2;
        ans += t1 * t2;
    }
    cout << ans;
}