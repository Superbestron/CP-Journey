#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, level = 1; cin >> n >> m;
    vector<string> v(n);
    int arr[n][m];
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = v[i][j] == '.' ? 0 : -1;
        }
    }
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Main idea here is to iteratively fill in the numbers in increasing order
    // We stop the while loop once there is not a single update during the 2 for loops
    while (true) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (arr[i][j] != -1) continue;
                update = true;
                int mini = 101;
                for (auto & direction : directions) {
                    int x = i + direction[0];
                    int y = j + direction[1];
                    if (x < 0 || x >= n || y < 0 || y >= m) {
                        mini = min(mini, 0);
                    } else if (arr[x][y] == -1) {
                        continue;
                    } else {
                        mini = min(mini, arr[x][y]);
                    }
                }
                if (mini + 1 == level) {
                    arr[i][j] = mini + 1;
                }
            }
        }
        if (!update) break;
        level++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << '.';
            if (level >= 10 && arr[i][j] < 10) cout << '.';
            if (arr[i][j] == 0) cout << '.';
            else cout << arr[i][j];
        }
        cout<<endl;
    }
}