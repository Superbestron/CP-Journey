#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int tc = 1, ans, n, OK;
int arr[15];

void backtrack(int rw, int ld, int rd, int col) {
    // all bits in rw are on
    if (rw == OK) {
        ans++;
        return;
    }
    int pos = OK & (~(rw | ld | rd));                               // 1s in pos can be used
    int col_mask = 1 << col;
    while (pos) {                                                   // faster than O(n)
        int p = LSOne(pos);                                         // LSOne---this is fast
        pos -= p;                                                   // turn off that on bit
        int j = __builtin_ctz(p);
        if (!(arr[j] & col_mask)) continue;
        backtrack(rw | p, (ld | p) << 1, (rd | p) >> 1, col + 1); // clever
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> n && n != 0) {
        ans = 0;
        OK = (1 << n) - 1;
        for (int i = 0; i < n; i++) {
            cin >> s;
            int can = (1 << n) - 1;
            for (int j = 0; j < n; j++) {
                if (s[j] == '*') can &= (~(1 << j));
            }
            arr[i] = can;
        }
        backtrack(0, 0, 0, 0); // the starting point
        cout << "Case " << tc++ << ": " << ans << '\n';
    }
}