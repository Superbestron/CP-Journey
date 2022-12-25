#include <iostream>
#include <vector>

using namespace std;

int k, maxR, maxC;

int calc(vector<string>& v, int i, int j) {
    int total = 0;
    for (int l = 1; l < k - 1; l++) {
        for (int m = 1; m < k - 1; m++) {
            if (v[i + l][m + j] == '*') {
                total++;
            }
        }
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, s, ans = 0;
    cin >> r >> s >> k;
    vector<string> v(r);
    for (int i = 0; i < r; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < r - k + 1; i++) {
        for (int j = 0; j < s - k + 1; j++) {
            int sol = calc(v, i, j);
            if (sol > ans) {
                ans = sol;
                maxR = i;
                maxC = j;
            }
        }
    }
    cout << ans << endl;
    // Create the sides
    for(int i = 0; i < k; i++) {
        v[maxR][maxC+i] = '-';
        v[maxR+k-1][maxC+i] = '-';
        v[maxR+i][maxC] = '|';
        v[maxR+i][maxC+k-1] = '|';
    }

    // Create the corners
    v[maxR][maxC] = '+';
    v[maxR+k-1][maxC] = '+';
    v[maxR][maxC+k-1] = '+';
    v[maxR+k-1][maxC+k-1] = '+';

    for(auto& i : v) {
        cout << i << endl;
    }
}