#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, t, ans = 0; cin >> n;
    bool arr[366];
    memset(arr, false, sizeof arr);
    while (n--) {
        cin >> s >> t;
        for (int i = s; i <= t; i++) arr[i] |= true;
    }
    for (int i = 1; i <= 365; i++) {
        if (arr[i]) ans++;
    }
    cout << ans;
}