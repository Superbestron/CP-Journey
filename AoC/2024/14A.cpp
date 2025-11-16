#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Simply get the final position of each robot after 100 seconds and place it in the Hashmap.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int m = 101, n = 103;
    vii positions;
    map<int, map<int, int>> cnts;
    while (getline(cin, s)) {
        vector<string> t = split(s, ' ');
        vector<string> p = split(t[0], ',');
        vector<string> v = split(t[1], ',');
        int x = stoi(split(p[0], '=')[1]);
        int y = stoi(p[1]);
        int vx = stoi(split(v[0], '=')[1]);
        int vy = stoi(v[1]);
        int final_x = (m + (x + (vx * 100)) % m) % m;
        int final_y = (n + (y + (vy * 100)) % n) % n;
        cnts[final_x][final_y]++;
    }
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (auto& [x, mp] : cnts) {
        for (auto &[y, cnt] : mp) {
            if (x < m / 2) {
                if (y < n / 2) q1 += cnt;
                else if (y > n / 2 ) q2 += cnt;
            } else if (x > m / 2) {
                if (y < n / 2) q3 += cnt;
                else if (y > n / 2 ) q4 += cnt;
            }
        }
    }
    cout << q1 * q2 * q3 * q4 << '\n';
}
