#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, n, temp, ans = 0;
    cin >> x >> n;
    while (n-- > 0) {
        cin >> temp;
        ans += x - temp;
    }
    cout << ans + x;
}