#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n, dvd; cin >> k;
    while (k--) {
        cin >> n;
        int curr = 0;
        for (int i = 0; i < n; i++) {
            cin >> dvd;
            if (dvd == curr + 1) curr++;
        }
        cout << n - curr << '\n';
    }
}