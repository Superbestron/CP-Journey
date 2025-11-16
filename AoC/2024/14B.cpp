#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// I can't think of any other way other than brute-force and "eyeball" the christmas tree. I highly recommend printing
// out the position of the robots after each second. I put eyeball in quotation marks because you can actually use grep
// or whatever search tool to search the output for a series of consecutive robots.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int m = 101, n = 103;
    vii positions;
    vector<vi> grid(m, vi(n));
    vector<tuple<int, int, int, int>> vec;
    while (getline(cin, s)) {
        vector<string> t = split(s, ' ');
        vector<string> p = split(t[0], ',');
        vector<string> v = split(t[1], ',');
        int x = stoi(split(p[0], '=')[1]);
        int y = stoi(p[1]);
        int vx = stoi(split(v[0], '=')[1]);
        int vy = stoi(v[1]);
        grid[x][y]++;
        vec.emplace_back(x, y, vx, vy);
    }
    for (int i = 0; i < 10000; i++) {
        for (auto& [x, y, vx, vy] : vec) {
            grid[x][y]--;
            x = (x + vx + m) % m;
            y = (y + vy + n) % n;
            grid[x][y]++;
        }
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                if (grid[j][k] == 0) cout << '.';
                else cout << 'X';
            }
            cout << '\n';
        }
        cout << "This is the " << i + 1 << " iteration.\n";
        cout << '\n';
    }
}
