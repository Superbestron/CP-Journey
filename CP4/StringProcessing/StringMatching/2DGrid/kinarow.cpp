#include <bits/stdc++.h>

using namespace std;

int L, M, N, K, H = 0, G = 0;
string board[200];

bool checkBoard(char c) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // down
            if (i + K <= N) {
                bool down = true;
                for (int k = i; k - i < K; k++) {
                    if (board[k][j] != c) {
                        down = false;
                        break;
                    }
                }
                if (down) return true;
            }
            // right
            if (j + K <= M) {
                bool right = true;
                for (int k = j; k - j < K; k++) {
                    if (board[i][k] != c) {
                        right = false;
                        break;
                    }
                }
                if (right) return true;
            }
            // top left to btm right
            if (i + K <= N && j + K <= M) {
                bool diag1 = true;
                for (int k1 = i, k2 = j; k1 - i < K; k1++, k2++) {
                    if (board[k1][k2] != c) {
                        diag1 = false;
                        break;
                    }
                }
                if (diag1) return true;
            }
            // bottom left to top right
            if (i - K + 1 >= 0 && j + K <= M) {
                bool diag2 = true;
                for (int k1 = i, k2 = j; k2 - j < K; k1--, k2++) {
                    if (board[k1][k2] != c) {
                        diag2 = false;
                        break;
                    }
                }
                if (diag2) return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> L;
    while (L--) {
        cin >> M >> N >> K;
        for (int i = 0; i < N; i++) cin >> board[i];
        if (checkBoard('x')) H++;
        else if (checkBoard('o')) G++;
    }
    printf("%d:%d", H, G);
}