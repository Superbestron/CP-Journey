#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> board(8);
    for (int i = 0; i < 8; i++) cin >> board[i];
    string s; cin >> s;
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int x = 7, y = 0, curr_dir = 1;
    for (int i = 0; i < s.size(); i++) {
        int new_x, new_y;
        if (s[i] == 'F') {
            new_x = x + directions[curr_dir][0], new_y = y + directions[curr_dir][1];
            if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8 || board[new_x][new_y] == 'C' || board[new_x][new_y] == 'I') {
                cout << "Bug!";
                return 0;
            }
            x = new_x, y = new_y;
        } else if (s[i] == 'L') {
            curr_dir = (curr_dir + 3) % 4;
        } else if (s[i] == 'R') {
            curr_dir = (curr_dir + 1) % 4;
        } else {
            new_x = x + directions[curr_dir][0];
            new_y = y + directions[curr_dir][1];
            if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8 || board[new_x][new_y] != 'I') {
                cout << "Bug!"; return 0;
            }
            board[new_x][new_y] = '.';
        }
    }
    if (board[x][y] == 'D') cout << "Diamond!";
    else cout << "Bug!";
}