#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, n;
    cin >> x >> y >> n;
    vector<string> v(n);
    string directions[3] = {"Forward", "Left", "Right"};
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) {
        string original = v[i];
        for (auto& j : directions) {
            if (v[i] == j) continue;
            v[i] = j;
            int curr_x = 0, curr_y = 0, direction = 0;
            for (int k = 0; k < n; k++) {
                if (v[k] == directions[0]) {
                    if (direction == 0) curr_y++;
                    else if (direction == 1) curr_x++;
                    else if (direction == 2) curr_y--;
                    else curr_x--;
                } else if (v[k] == directions[1]) direction = (direction - 1 + 4) % 4;
                else direction = (direction + 1) % 4;
            }
            if (curr_x == x && curr_y == y) {
                cout << i + 1 << ' ' << j;
                return 0;
            }
            v[i] = original;
        }
    }
}