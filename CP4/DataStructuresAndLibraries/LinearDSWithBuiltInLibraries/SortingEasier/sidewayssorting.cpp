#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int r = 1, c = 1;
    cin >> r >> c;
    while (r != 0 && c != 0) {
        string rows[r];
        string cols[c];
        for (int i = 0; i < r; i++) {
            cin >> rows[i];
        }

        auto is_sensitive = [](auto& left, auto& right) {
            for (int i = 0; i < left.size(); i++) {
                if (tolower(left[i]) < tolower(right[i])) {
                    return true;
                } else if (tolower(left[i]) > tolower(right[i])) {
                    return false;
                }
            }
            return false;
        };

        for (int i = 0; i < c; i++) {
            string str;
            for (int j = 0; j < r; j++) {
                str += rows[j][i];
            }
            cols[i] = str;
        }
        stable_sort(cols, cols + c, is_sensitive);
        fill(rows, rows + r, "");
        for (int i = 0; i < c; i++) {
            for (int j = 0; j < r; j++) {
                rows[j] += cols[i][j];
            }
        }
        for (int i = 0; i < r; i++) cout << rows[i] << endl;
        cin >> r >> c;
        cout << endl;
    }
}
