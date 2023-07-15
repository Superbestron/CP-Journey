#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int y; cin >> y;
    if (y == 2018) {
        cout << "yes";
        return 0;
    }
    int first = (y - 2019) * 12 + 8;
    int second = (y - 2018) * 12 + 8;
    if (first / 26 != second / 26) cout << "yes";
    else cout << "no";
}