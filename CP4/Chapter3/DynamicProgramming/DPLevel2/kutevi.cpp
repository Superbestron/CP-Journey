#include <iostream>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, val;
    cin >> n >> k;
    bitset<360> dp;
    while (n-- > 0) {
        cin >> val;
        int c = val;
        while (!dp[c]) {
            dp.flip(c);
            c = (c + val) % 360;
        }
    }
    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < 360; j++) {
            if (dp[i] && dp[j] && !dp[(i + j) % 360]) dp[(i + j) % 360].flip();
        }
    }
    while (k-- > 0) {
        cin >> val;
        if (dp[val]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
};