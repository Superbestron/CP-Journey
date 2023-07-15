#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int table[4][4];
    int new_table[4][4];
    int direction;
    vector<stack<int>> v;
    for (auto & i : table) {
        for (int & j : i) {
            cin >> j;
        }
    }
    cin >> direction;
    if (direction == 0) { // left
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                new_table[3 - j][i] = table[i][j];
            }
        }
    } else if (direction == 2) { // right
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                new_table[j][3 - i] = table[i][j];
            }
        }
    } else if (direction == 1) { // up
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                new_table[3 - i][j] = table[i][j];
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                new_table[i][j] = table[i][j];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        // shift down numbers
        int ptr = 3;
        for (int j = 3; j >= 0; j--) {
            if (new_table[j][i] == 0) {
                continue;
            }
            new_table[ptr--][i] = new_table[j][i];
        }
        for (int j = ptr; j >= 0; j--) {
            new_table[j][i] = 0;
        }
        stack<int> temp;
        for (int j = 3; j >= 0; j--) {
            // to push check if stack have same
            int curr = new_table[j][i];
            if (curr == 0) break;
            if (j != 0 && curr == new_table[j - 1][i]) {
                temp.push(curr * 2);
                j--;
            } else {
                temp.push(curr);
            }
        }
        v.emplace_back(temp);
    }

    for (int i = 0; i < v.size(); i++) {
        stack<int>& s = v[i];
        for (int j = 0; j < 4 - s.size(); j++) {
            new_table[j][i] = 0;
        }
        for (int j = 4 - s.size(); j < 4; j++) {
            new_table[j][i] = s.top();
            s.pop();
        }
    }

    // rotate back
    if (direction == 0) { // left
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                table[j][3 - i] = new_table[i][j];
            }
        }

    } else if (direction == 2) { // right
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                table[3 - j][i] = new_table[i][j];
            }
        }
    } else if (direction == 1) { // up
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                table[3 - i][j] = new_table[i][j];
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                table[i][j] = new_table[i][j];
            }
        }
    }

    for (auto & i : table) {
        for (int & j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
}
