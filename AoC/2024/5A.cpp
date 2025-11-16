#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// The input is actually a clique, so for each pair of pages in sequence, we just look up the Adjacency List to check.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<int, unordered_set<int>> AL;
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
            if (can) ans += nums[nums.size() / 2];
        }
    }
    cout << ans << '\n';
}
