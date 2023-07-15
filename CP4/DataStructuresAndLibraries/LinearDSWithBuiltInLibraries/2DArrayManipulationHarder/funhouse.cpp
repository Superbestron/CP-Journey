#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Idea is simple but implementation might be tricky
// I like to define my direction and its corresponding direction coordinates clearly

int main() {
    ios_base::sync_with_stdio(false);
    string str;
    int direction, w, l, x, y, house = 1;
    // up, down, left, right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (cin >> w >> l && w != 0 && l != 0) {
        vector<string> v(l);
        for (int i = 0; i < l; i++) {
            cin >> v[i];
            for (int j = 0; j < w; j++) {
                if (v[i][j] == '*') x = i, y = j;
            }
        }

        if (x == 0) direction = 1;
        else if (x == l - 1) direction = 0;
        else if (y == 0) direction = 3;
        else direction = 2;

        while (true) {
            x += directions[direction][0];
            y += directions[direction][1];
            if (direction == 0) {
                if (v[x][y] == '/') direction = 3;
                else if (v[x][y] == '\\') direction = 2;
            } else if (direction == 1) {
                if (v[x][y] == '/') direction = 2;
                else if (v[x][y] == '\\') direction = 3;
            } else if (direction == 2) {
                if (v[x][y] == '/') direction = 1;
                else if (v[x][y] == '\\') direction = 0;
            } else {
                if (v[x][y] == '/') direction = 0;
                else if (v[x][y] == '\\') direction = 1;
            }

            // we have reached the exit
            if (x == 0 || x == l - 1 || y == 0 || y == w - 1) {
                v[x][y] = '&';
                break;
            }
        }
        cout << "HOUSE " << house++ << endl;
        for (auto& s : v) cout << s << endl;
    }
}
