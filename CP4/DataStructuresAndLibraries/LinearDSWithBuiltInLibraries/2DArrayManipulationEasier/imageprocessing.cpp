#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int h, w, n, m, curr;
    cin >> h >> w >> n >> m;
    int image[h][w];
    int kernel[n][m];
    int answer[h - n + 1][w - m + 1];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> curr;
            image[i][j] = curr;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> curr;
            kernel[i][j] = curr;
        }
    }

    for (int i = 0; i < h - n + 1; i++) {
        for (int j = 0; j < w - m + 1; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < m; l++) {
                    // i = 0, j = 1
                    sum += image[i + k][j + l] * kernel[n - k - 1][m - l - 1];
                }
            }
            answer[i][j] = sum;
        }
    }
    for (int i = 0; i < h - n + 1; i++) {
        for (int j = 0; j < w - m + 1; j++) {
            cout << answer[i][j] << ' ';
        }
        cout << endl;
    }
}