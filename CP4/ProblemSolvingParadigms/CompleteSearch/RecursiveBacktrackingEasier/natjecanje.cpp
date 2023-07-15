#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int recurse(vector<int>& damaged, unordered_set<int>& reserve) {
    if (damaged.empty()) return 0;
    int x = damaged.back();
    int ans = 999;

    // get left
    if (reserve.count(x - 1) == 1) {
        damaged.pop_back();
        reserve.erase(x - 1);
        ans = min(ans, recurse(damaged, reserve));
        damaged.push_back(x);
        reserve.insert(x - 1);
    }
    // get right
    if (reserve.count(x + 1) == 1) {
        damaged.pop_back();
        reserve.erase(x + 1);
        ans = min(ans, recurse(damaged, reserve));
        damaged.push_back(x);
        reserve.insert(x + 1);
    }

    damaged.pop_back(); // ignore the damaged
    return min(ans, 1 + recurse(damaged, reserve));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, r, i, temp;
    cin >> n >> s >> r;
    vector<int> damaged;
    unordered_set<int> d, reserve;
    for (i = 0; i < s; i++) {
        cin >> temp;
        d.insert(temp);
    }
    for (i = 0; i < r; i++) {
        cin >> temp;
        reserve.insert(temp);
    }
    for (int j : d) {
        if (reserve.count(j) == 1) {
            reserve.erase(j);
        } else {
            damaged.push_back(j);
        }
    }
    cout << recurse(damaged, reserve);
}