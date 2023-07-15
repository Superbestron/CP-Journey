#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, b; cin >> n;
    while (n--) {
        cin >> b;
        for (int i = 0; i < 1 << 8; i++) {
            if ((i ^ ((i << 1) & 255)) == b) {
                cout << i << ' ';
                break;
            }
        }
    }
}