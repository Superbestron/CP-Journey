#include <bits/stdc++.h>

using namespace std;

char arr[100][100];
string target = "ICPCASIASG";
int N;
int directions[8][2] = {{1, 2}, {1, -2}, {2, 1}, {-2, 1}, {-1, -2}, {-1, 2}, {-2, -1}, {2, -1}};

bool dfs(int depth, int x, int y) {
    if (depth == target.size()) return true;
    for (auto& direction : directions) {
        int new_x = x + direction[0];
        int new_y = y + direction[1];
        if (new_x < 0 || new_x >= N || new_y < 0 || new_y >= N) continue;
        if (arr[new_x][new_y] == target[depth]) {
            if (dfs(depth + 1, new_x, new_y)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    bool printed = false;
    for (int j = 0; !printed && j < N; j++) {
        for (int k = 0; !printed && k < N; k++) {
            if (arr[j][k] == target[0] && dfs(1, j, k)) printed = true;
        }
    }
    if (printed) cout << "YES\n";
    else cout << "NO\n";
}