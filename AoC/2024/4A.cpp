#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Brute-force check 8 directions for each point in grid.

int main() {
    vector<string> v;
    string s;
    while (cin >> s) {
        v.push_back(s);
    }
    int ans = 0, h = v.size(), w = v[0].size();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // check all 8 dirs
            if (j + 3 < w) {
                if (v[i][j] == 'X' && v[i][j + 1] == 'M' && v[i][j + 2] == 'A' && v[i][j + 3] == 'S') ans++;
            }
            if (j + 3 < w && i + 3 < h) {
                if (v[i][j] == 'X' && v[i + 1][j + 1] == 'M' && v[i + 2][j + 2] == 'A' && v[i + 3][j + 3] == 'S') ans++;
            }
            if (i + 3 < h) {
                if (v[i][j] == 'X' && v[i + 1][j] == 'M' && v[i + 2][j] == 'A' && v[i + 3][j] == 'S') ans++;
            }
            if (j - 3 >= 0 && i + 3 < h) {
                if (v[i][j] == 'X' && v[i + 1][j - 1] == 'M' && v[i + 2][j - 2] == 'A' && v[i + 3][j - 3] == 'S') ans++;
            }
            if (j - 3 >= 0) {
                if (v[i][j] == 'X' && v[i][j - 1] == 'M' && v[i][j - 2] == 'A' && v[i][j - 3] == 'S') ans++;
            }
            if (j - 3 >= 0 && i - 3 >= 0) {
                if (v[i][j] == 'X' && v[i - 1][j - 1] == 'M' && v[i - 2][j - 2] == 'A' && v[i - 3][j - 3] == 'S') ans++;
            }
            if (i - 3 >= 0) {
                if (v[i][j] == 'X' && v[i - 1][j] == 'M' && v[i - 2][j] == 'A' && v[i - 3][j] == 'S') ans++;
            }
            if (j + 3 < w && i - 3 >= 0) {
                if (v[i][j] == 'X' && v[i - 1][j + 1] == 'M' && v[i - 2][j + 2] == 'A' && v[i - 3][j + 3] == 'S') ans++;
            }
        }
    }
    cout << ans << '\n';
}
