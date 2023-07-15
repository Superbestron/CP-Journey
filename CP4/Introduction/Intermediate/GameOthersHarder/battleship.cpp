#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, w, h, n, x, y; cin >> t;
    while (t--) {
        cin >> w >> h >> n;
        string p1[h], p2[h];
        int ships[2]; memset(ships, 0, sizeof ships);
        bool is_player_one = true, end = false;
        for (int i = 0; i < h; i++) {
            cin >> p1[i];
            for (char c : p1[i]) {
                if (c == '#') ships[0]++;
            }
        }
        for (int i = 0; i < h; i++) {
            cin >> p2[i];
            for (char c : p2[i]) {
                if (c == '#') ships[1]++;
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            if (end) continue;
            if (is_player_one) {
                if (p2[h - y - 1][x] == '#') {
                    p2[h - y - 1][x] = '_';
                    ships[1]--;
                    if (ships[1] == 0) {
                        is_player_one = false;
                    }
                } else {
                    is_player_one = false;
                }
            } else {
                if (p1[h - y - 1][x] == '#') {
                    p1[h - y - 1][x] = '_';
                    ships[0]--;
                    if (ships[0] == 0) {
                        is_player_one = false;
                        end = true;
                    }
                } else {
                    is_player_one = true;
                    // we have finished one turn
                    if (ships[0] * ships[1] == 0)
                    end = true;
                }
            }
        }
        if (ships[0] == 0 && ships[1] > 0)
            cout << "player two wins\n";
        else if (ships[0] > 0  && ships[1] == 0)
            cout << "player one wins\n";
        else cout << "draw\n";
    }
}
