#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int val1, val2, total = 0;
    vector<pair<int, int>> v;
    set<pair<int, int>> s;
    while (n--) {
        cin >> val1 >> val2;
        v.emplace_back(val1, val2);
        s.emplace(val1, val2);
    }

    // To cut down on runtime can sort first, so we minimise checking of points later
    sort(v.begin(), v.end());

    // Key Idea is 1118^2 + 1680^2 = 2018^2 (pythagorean triple)
    for (auto& p : v) {
        vector<pair<int, int>> temp;
        temp.emplace_back(p.first, p.second + 2018);
        temp.emplace_back(p.first + 1118, p.second + 1680);
        temp.emplace_back(p.first + 1680, p.second + 1118);
        temp.emplace_back(p.first + 2018, p.second);
        temp.emplace_back(p.first + 1118, p.second - 1680);
        temp.emplace_back(p.first + 1680, p.second - 1118);
        for (auto& p2 : temp) {
            if (s.count(p2) == 1) total++;
        }
    }
    cout << total;
}
