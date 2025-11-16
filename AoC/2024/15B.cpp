#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// This is actually quite tricky, after you realise that pushing boxes up and down can potentially trigger a whole push
// of a "pyramid" of boxes. The most natural way is to check them recursively. Recursively check to see if we are able
// to push whatever is ahead of the current box by 1 step forward. And if it's possible, then we again recursively
// do the push operation. Pushing left and right is exactly the same as 15A.

// up right down left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
unordered_map<char, int> mp;

bool can_push(vector<string>& grid, int i, int j, int dir) {
    int new_i = i + dirs[dir][0];
    int new_j = j + dirs[dir][1];
    if (grid[i][j] == '[') {
        if (grid[new_i][new_j] == '#') return false;
        else return can_push(grid, new_i, new_j, dir) && can_push(grid, new_i, new_j + 1, dir);
    } else if (grid[i][j] == ']') {
        if (grid[new_i][new_j] == '#') return false;
        else return can_push(grid, new_i, new_j, dir) && can_push(grid, new_i, new_j - 1, dir);
    } else return (grid[i][j] == '.');
}

void push(vector<string>& grid, int i, int j, int dir) {
    int new_i = i + dirs[dir][0];
    int new_j = j + dirs[dir][1];
    if (grid[i][j] == '[') {
        push(grid, new_i, new_j, dir);
        push(grid, new_i, new_j + 1, dir);
        grid[new_i][new_j] = '[', grid[new_i][new_j + 1] = ']';
        grid[i][j] = '.', grid[i][j + 1] = '.';
    } else if (grid[i][j] == ']') {
        push(grid, new_i, new_j, dir);
        push(grid, new_i, new_j - 1, dir);
        grid[new_i][new_j] = ']', grid[new_i][new_j - 1] = '[';
        grid[i][j] = '.', grid[i][j - 1] = '.';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, commands;
    vector<string> grid;
    ii start;
    while (getline(cin, s)) {
        string actual;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '@') {
                start = make_pair(grid.size(), 2 * i);
                s[i] = '.';
            }
            if (s[i] == '#') actual += "##";
            else if (s[i] == 'O') actual += "[]";
            else actual += "..";
        }
        if (s.empty()) break;
        grid.push_back(actual);
    }
    while (cin >> s) commands += s;
    int m = grid.size(), n = grid[0].size(), ans = 0;
    mp['^'] = 0, mp['>'] = 1, mp['v'] = 2, mp['<'] = 3;
    int x = start.first, y = start.second;
    for (char c : commands) {
        auto& dir = dirs[mp[c]];
        int new_x = x + dir[0], new_y = y + dir[1];
        char new_c = grid[new_x][new_y];
        if (new_c == '.') {
            x = new_x, y = new_y;
        } else if (new_c == '[' || new_c == ']') {
            if (c == '^' || c == 'v') {
                if (can_push(grid, new_x, new_y, mp[c])) {
                    push(grid, new_x, new_y, mp[c]);
                    x = new_x, y = new_y;
                }
            } else {
                int pot_x = new_x, pot_y = new_y;
                while (true) {
                    if (grid[pot_x][pot_y] == '#') break;
                    else if (grid[pot_x][pot_y] == '.') {
                        if (c == '>') {
                            for (int j = new_y; j <= pot_y; j++) {
                                if ((j ^ new_y) & 1) grid[pot_x][j] = '[';
                                else grid[pot_x][j] = ']';
                            }
                        } else {
                            for (int j = new_y; j >= pot_y; j--) {
                                if ((j ^ new_y) & 1) grid[pot_x][j] = ']';
                                else grid[pot_x][j] = '[';
                            }
                        }
                        grid[new_x][new_y] = '.';
                        x = new_x, y = new_y;
                        break;
                    }
                    pot_x += dir[0], pot_y += dir[1];
                }
            }
        }
    }
    for (int i = 1; i < m - 1; i++) {
        for (int j = 2; j < n - 2; j++) {
            if (grid[i][j] == '[') ans += 100 * i + j;
        }
    }
    cout << ans << '\n';
}
