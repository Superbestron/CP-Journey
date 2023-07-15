#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m; cin >> m; cin.ignore();
    string name, s;
    unordered_map<string, int> map;
    unordered_map<string, unordered_set<string>> v;
    vector<pair<string, int>> pairs;
    for (int i = 0; i < m; i++) {
        getline(cin, s);
        istringstream parse(s);
        parse >> name;
        while (parse >> s) {
            map[s]++;
            v[name].emplace(s);
        }
    }
    for (auto it = map.begin(); it != map.end();) {
        bool to_delete = false;
        for (auto& set : v) {
            if (!set.second.count(it->first)) {
                it = map.erase(it);
                to_delete = true;
                break;
            }
        }
        if (!to_delete) it++;
    }
    if (map.empty()) cout << "ALL CLEAR";
    else {
        for (auto& p : map) pairs.emplace_back(p);
        auto cmp = [](auto& p1, auto& p2) {
            if (p1.second == p2.second) return p1.first < p2.first;
            return p1.second > p2.second;
        };
        sort(pairs.begin(), pairs.end(), cmp);
        for (auto& pair : pairs) {
            cout << pair.first << endl;
        }
    }
}
