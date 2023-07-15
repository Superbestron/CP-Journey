#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, m, points; cin >> n >> p >> m;
    bool winners = false;
    unordered_map<string, int> map;
    string s;
    while (n--) {
        cin >> s;
        map[s] = 0;
    }
    while (m--) {
        cin >> s >> points;
        if (map.count(s) == 0) continue;
        map[s] += points;
        if (map[s] >= p) {
            cout << s << " wins!" << endl;
            winners = true;
            map.erase(s);
        }
    }
    if (!winners) cout << "No winner!";
}
