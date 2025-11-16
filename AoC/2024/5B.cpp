#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// One of the initial mistakes I made at the start was to assume there was a total order among all the nodes,
// where I could do a topological sort on the entire input. Turns out this was not the case, so we have to resort to
// doing topological sort per test case, in which we are guaranteed a total order over this subset. Once we have this
// order, it's a matter of sorting the nodes internally in this subset, which gives the correctly-ordered update. Use
// 5A as a subroutine to identify incorrectly-ordered updates.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<int, unordered_set<int>> AL;
    queue<int> q;
    string s;
    bool first = true;
    int ans = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            first = false;
            continue;
        }
        if (first) {
            int num1 = stoi(s.substr(0, 2));
            int num2 = stoi(s.substr(3, 2));
            AL[num1].insert(num2);
        } else {
            vi nums;
            int pos = 0;
            while (pos < s.size()) {
                nums.push_back(stoi(s.substr(pos, 2)));
                pos += 3;
            }
            bool can = true;
            for (int i = 1; i < nums.size(); i++) {
                if (!AL[nums[i - 1]].count(nums[i])) {
                    can = false;
                    break;
                }
            }

            if (!can) {
                unordered_map<int, unordered_set<int>> s_AL;
                unordered_set<int> nums_map(nums.begin(), nums.end());
                unordered_map<int, int> deg, ord;
                for (auto& [k, v] : AL) {
                    if (!nums_map.count(k)) continue;
                    for (int o : v) {
                        if (nums_map.count(o)) {
                            s_AL[k].insert(o);
                            deg[o]++;
                        }
                    }
                }
                for (int num : nums) {
                    if (deg[num] == 0) q.push(num);
                }
                int order = 0;
                while (!q.empty()) {
                    int node = q.front(); q.pop();
                    ord[node] = order++;
                    for (int o : AL[node]) {
                        deg[o]--;
                        if (deg[o] == 0) q.push(o);
                    }
                }
                vii ord_pair;
                for (int i : nums) ord_pair.emplace_back(i, ord[i]);
                auto comparator = [&](auto& i1, auto& i2) {
                    return i1.second < i2.second;
                };
                sort(ord_pair.begin(), ord_pair.end(), comparator);
                ans += ord_pair[nums.size() / 2].first;
            }
        }
    }
    cout << ans << '\n';
}
