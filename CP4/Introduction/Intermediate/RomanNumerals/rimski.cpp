#include <bits/stdc++.h>

using namespace std;

// Requires some keen observation: tricky problem

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string B; cin >> B;
    if (B.size() >= 2) {
        // Greedily swap VI to IV
        if (B[B.size() - 2] == 'V' && B.back() == 'I') {
            B[B.size() - 2] = 'I';
            B[B.size() - 1] = 'V';
        }
        // Edge case
        if (B == "LXI") {
            cout << "XLI"; return 0;
        }
        // Greedily swap XI to IX, so that LXXI -> XLIX
        if (B[B.size() - 2] == 'X' && B.back() == 'I') {
            B[B.size() - 2] = 'I';
            B[B.size() - 1] = 'X';
        }
        if (B[0] == 'L' && B[1] == 'X' && B[2] != 'X') {
            B[0] = 'X';
            B[1] = 'L';
        }
    }
    cout << B;
}