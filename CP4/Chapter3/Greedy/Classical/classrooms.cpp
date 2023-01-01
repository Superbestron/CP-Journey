#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, ans = 0; cin >> n >> k;
    vector<pair<int, int>> v;
    map<int, int> ms;
    for (int i = 0; i < n; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        v.emplace_back(p1, p2);
    }
    auto comparator = [](auto& p1, auto& p2) {
        return p1.second < p2.second;
    };
    sort(v.begin(), v.end(), comparator);

    // use ms to keep track of end points
    for (int i = 0; i < k; i++) ms[0]++;
    for (int i = 0; i < n; i++) {
        auto it = ms.lower_bound(v[i].first); // give me the one with the greatest starting time
        if (it == ms.begin()) continue;
        it--;
        ms[it->first]--;
        if (ms[it->first] == 0) ms.erase(it->first);
        ans++;
        ms[v[i].second]++;
    }

    cout << ans;
}