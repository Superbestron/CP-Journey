#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Similar style as 7A, with an additional implementation detail.

bool recurse(vi& nums, int idx, ll curr, ll target, int op) {
    if (curr > target) return false;
    if (nums.size() == idx) {
        return curr == target;
    }
    bool ans = false;
    if (op == 0) {
        ans |= recurse(nums, idx + 1, curr + nums[idx], target, 0);
        ans |= recurse(nums, idx + 1, curr + nums[idx], target, 1);
        ans |= recurse(nums, idx + 1, curr + nums[idx], target, 2);
    } else if (op == 1) {
        ans |= recurse(nums, idx + 1, curr * nums[idx], target, 0);
        ans |= recurse(nums, idx + 1, curr * nums[idx], target, 1);
        ans |= recurse(nums, idx + 1, curr * nums[idx], target, 2);
    } else {
        string s1 = to_string(curr), s2 = to_string(nums[idx]);
        ll num = stoll(s1 + s2);
        ans |= recurse(nums, idx + 1, num, target, 0);
        ans |= recurse(nums, idx + 1, num, target, 1);
        ans |= recurse(nums, idx + 1, num, target, 2);
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
        if (recurse(nums, 1, nums[0], tot, 0)
            || recurse(nums, 1, nums[0], tot, 1)
            || recurse(nums, 1, nums[0], tot, 2)) ans += tot;
    }
    cout << ans << '\n';
}
