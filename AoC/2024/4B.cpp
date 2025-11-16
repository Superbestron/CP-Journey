#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Similar brute-force style as 4A except checking conditions are different.

int main() {
    vector<string> v;
    string s;
    while (cin >> s) {
        v.push_back(s);
    }
    int ans = 0, h = v.size(), w = v[0].size();
    for (int i = 1; i < h - 1; i++) {
        for (int j = 1; j < w - 1; j++) {
            if (v[i][j] != 'A') continue;
            if (v[i - 1][j - 1] == 'M') {
                if (v[i + 1][j - 1] == 'M') {
                    if (v[i - 1][j + 1] == 'S' && v[i + 1][j + 1] == 'S') ans++;
                } else if (v[i + 1][j - 1] == 'S') {
                    if (v[i - 1][j + 1] == 'M' && v[i + 1][j + 1] == 'S') ans++;
                }
            } else if (v[i - 1][j - 1] == 'S') {
                if (v[i + 1][j - 1] == 'S') {
                    if (v[i - 1][j + 1] == 'M' && v[i + 1][j + 1] == 'M') ans++;
                } else if (v[i + 1][j - 1] == 'M') {
                    if (v[i - 1][j + 1] == 'S' && v[i + 1][j + 1] == 'M') ans++;
                }
            }
        }
    }
    cout << ans << '\n';
}
