#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, ans = 0;
    string str;
    cin >> n >> m;
    vector<string> v;
    while (n-- > 0) {
        cin >> str;
        v.emplace_back(str);
    }
    for (int j = 0; j < m; j++) {
        bool empty = true;
        for (int i = 0; i < v.size(); i++) {
            if (v[i][j] == '$') {
                empty = false;
                break;
            }
        }
        if (empty) ans++;
    }
    cout << ans + 1;
}