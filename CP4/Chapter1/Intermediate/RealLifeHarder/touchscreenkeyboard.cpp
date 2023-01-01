#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

char top[10] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
char mid[9] = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
char btm[8] = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};

int dist(char c1, char c2) {
    if (c1 == c2) return 0;
    int h1, h2, pos1, pos2;
    for (int i = 0; i < 10; i++) {
        if (top[i] == c1) {
            h1 = 0, pos1 = i;
        } else if (top[i] == c2) {
            h2 = 0, pos2 = i;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (mid[i] == c1) {
            h1 = 1, pos1 = i;
        } else if (mid[i] == c2) {
            h2 = 1, pos2 = i;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (btm[i] == c1) {
            h1 = 2, pos1 = i;
        } else if (btm[i] == c2) {
            h2 = 2, pos2 = i;
        }
    }
    return abs(h1 - h2) + abs(pos1 - pos2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, l; cin >> t;
    string original, checker;
    while (t--) {
        vector<pair<string, int>> v;
        cin >> original >> l;
        while (l--) {
            cin >> checker;
            int val = 0;
            for (int i = 0; i < checker.size(); i++) val += dist(original[i], checker[i]);
            v.emplace_back(checker, val);
        }
        auto cmp = [](auto& p1, auto& p2) {
            if (p1.second == p2.second) return p1.first < p2.first;
            return p1.second < p2.second;
        };
        sort(v.begin(), v.end(), cmp);
        for (auto& p : v) cout << p.first << ' ' << p.second << endl;
    }
}
