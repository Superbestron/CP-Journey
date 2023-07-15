#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, curr;
    cin >> n >> m;
    vector<vector<int>> v;
    v.reserve(n);
    for (int j = 0; j < n; j++) {
        vector<int> inner;
        for (int i = 0; i < m; i++) {
            cin >> curr;
            inner.push_back(curr);

        }
        v.emplace_back(inner);
    }
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {
            // update right and down
            int up = 0, left = 0;
            if (i != 0) up = v[i - 1][j];
            if (j != 0) left = v[i][j - 1];
            v[i][j] += max(up, left);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << v[i][m - 1] << ' ';
    }
}