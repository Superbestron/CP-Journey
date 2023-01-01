#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, y, q, k; cin >> n;
    string s;
    unordered_map<string, vector<int>> m;
    while (n--) {
        cin >> s >> y;
        m[s].push_back(y);
    }
    for (auto& p : m) sort(p.second.begin(), p.second.end());
    cin >> q;
    while (q--) {
        cin >> s >> k;
        cout << m[s][k - 1] << endl;
    }
}
