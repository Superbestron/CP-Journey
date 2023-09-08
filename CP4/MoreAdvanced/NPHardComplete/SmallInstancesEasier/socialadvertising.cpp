#include <bits/stdc++.h>
using namespace std;

int t, n, d, j, ALL, AM[20];

int backtrack(int u, int mask, int sc_size) {
    if (mask == ALL) return sc_size;
    if (u == n) return 1e9;
    int op1 = backtrack(u + 1, mask, sc_size);
    int op2 = backtrack(u + 1, mask | AM[u], sc_size + 1);
    return min(op1, op2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        ALL = (1 << n) - 1;
        memset(AM, 0, sizeof AM);
        for (int i = 0; i < n; i++) {
            cin >> d;
            while (d--) {
                cin >> j; j--;
                AM[i] |= (1 << j);
                AM[j] |= (1 << i);
            }
            AM[i] |= (1 << i);
        }
        cout << backtrack(0, 0, 0) << '\n';
    }
}

