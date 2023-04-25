#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, a = 0, b = 0, c = 0, d = 0, e = 0;
    cin >> R >> C;
    string arr[R];
    for (int i = 0; i < R; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < R - 1; i++) {
        for (int j = 0; j < C - 1; j++) {
            char ctr = 'a';
            if (arr[i][j] == '#') continue;
            else if (arr[i][j] == 'X') ctr++;
            if (arr[i][j + 1] == '#') continue;
            else if (arr[i][j + 1] == 'X') ctr++;
            if (arr[i + 1][j] == '#') continue;
            else if (arr[i + 1][j] == 'X') ctr++;
            if (arr[i + 1][j + 1] == '#') continue;
            else if (arr[i + 1][j + 1] == 'X') ctr++;
            if (ctr == 'a') a++;
            else if (ctr == 'b') b++;
            else if (ctr == 'c') c++;
            else if (ctr == 'd') d++;
            else e++;
        }
    }
    cout << a << '\n';
    cout << b << '\n';
    cout << c << '\n';
    cout << d << '\n';
    cout << e << '\n';
}
