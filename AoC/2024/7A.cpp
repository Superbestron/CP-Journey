#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Brute-force try each operation per operand pair, this should give you (n - 1) ^ 2 possible operations for n operands.

bool recurse(vi& nums, int idx, ll curr, ll target, bool is_plus) {
    if (curr > target) return false;
    if (nums.size() == idx) {
        return curr == target;
    }
    bool ans = false;
    if (is_plus) {
        ans |= recurse(nums, idx + 1, curr + nums[idx], target, true);
        ans |= recurse(nums, idx + 1, curr + nums[idx], target, false);
    } else {
        ans |= recurse(nums, idx + 1, curr * nums[idx], target, true);
        ans |= recurse(nums, idx + 1, curr * nums[idx], target, false);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    ll ans = 0;
    while (getline(cin, s)) {
        vector<string> v = split(s, ':');
        ll tot = stoll(v[0]);
        istringstream str(v[1]);
        vi nums;
        int val;
        while (str >> val) nums.push_back(val);
        if (recurse(nums, 1, nums[0], tot, true) || recurse(nums, 1, nums[0], tot, false)) ans += tot;
    }
    cout << ans << '\n';
}
