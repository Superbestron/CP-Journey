#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// It's not algorithmically hard per se, but a clean implementation helps in doing the push. One way is to iteratively
// check forward to see if there is an additional space to push the block, then if available, "push" the blocks by
// copying the first block forward to the end, and erasing the first block.

// up right down left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
unordered_map<char, int> mp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, commands;
    vector<string> grid;
    ii start;
    while (getline(cin, s)) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '@') {
                start = make_pair(grid.size(), i);
                s[i] = '.';
            }
        }
        if (s.empty()) break;
        grid.push_back(s);
    }
    while (cin >> s) commands += s;
    int m = grid.size(), n = grid[0].size(), ans = 0;
    mp['^'] = 0, mp['>'] = 1, mp['v'] = 2, mp['<'] = 3;
    int x = start.first, y = start.second;
    for (char c : commands) {
        auto& dir = dirs[mp[c]];
        int new_x = x + dir[0];
        int new_y = y + dir[1];
        if (grid[new_x][new_y] == '.') {
            x = new_x, y = new_y;
        } else if (grid[new_x][new_y] == 'O') {
            int pot_x = new_x, pot_y = new_y;
            bool can_move = false;
            while (true) {
                if (grid[pot_x][pot_y] == '#') break;
                else if (grid[pot_x][pot_y] == '.') {
                    can_move = true;
                    grid[pot_x][pot_y] = 'O';
                    grid[new_x][new_y] = '.';
                    break;
                }
                pot_x += dir[0];
                pot_y += dir[1];
            }
            if (can_move) x = new_x, y = new_y;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'O') ans += 100 * i + j;
        }
    }
    cout << ans << '\n';
}
