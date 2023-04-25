#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, zr, zc;
    string s;
    cin >> r >> c >> zr >> zc;
    char ans[r * zr][c * zc];
    for (int i = 0; i < r; i++) {
        cin >> s;
        for (int j = 0; j < c; j++) {
            char character = s[j];
            for (int k = i * zr; k < (i + 1) * zr; k++) {
                for (int l = j * zc; l < (j + 1) * zc; l++) {
                    ans[k][l] = character;
                }
            }
        }
    }
    for (int i = 0; i < r * zr; i++) {
        for (int j = 0; j < c * zc; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}