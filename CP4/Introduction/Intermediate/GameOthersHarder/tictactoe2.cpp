#include <iostream>
#include <vector>

using namespace std;

bool check_win(vector<string>& board, char c) {
    // left col, top row
    return (board[0][0] == c && board[1][0] == c && board[2][0] == c || board[0][0] == c && board[0][1] == c && board[0][2] == c
    // left diagonal, btm row
        || board[0][0] == c && board[1][1] == c && board[2][2] == c || board[2][0] == c && board[2][1] == c && board[2][2] == c
        // right col, mid row
        || board[0][2] == c && board[1][2] == c && board[2][2] == c || board[1][0] == c && board[1][1] == c && board[1][2] == c
        // mid col, right diag
        || board[0][1] == c && board[1][1] == c && board[2][1] == c || board[0][2] == c && board[1][1] == c && board[2][0] == c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        vector<string> board(3);
        int x = 0, o = 0;
        for (int j = 0; j < 3; j++) cin >> board[j];

        // test.txt validity
        // count no of x, no of y
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (board[j][k] == 'X') x++;
                else if (board[j][k] == 'O') o++;
            }
        }
        if (o > x || x > o + 1) {
            cout << "no" << endl;
            continue;
        }

        // check win conditions
        bool x_win  = check_win(board, 'X');
        bool o_win = check_win(board, 'O');
        if (x_win && o_win || x_win && x == o || o_win && x == o + 1) {
            cout << "no" << endl;
            continue;
        }
        cout << "yes" << endl;
    }
}