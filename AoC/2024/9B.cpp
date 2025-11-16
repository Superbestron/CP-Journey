#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// The elegant approach in 9A doesn't work anymore, so we need to resort to a more brute-force style approach where we
// we greedily try to fit in each block from the back starting from free spaces from the left.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vi nums, v_ans;
    string s;
    vii spaces, blocks; // (idx, size)
    ll ans = 0;
    cin >> s;
    istringstream str(s);
    for (char c : s) nums.push_back(c - '0');
    for (int i = 0; i < nums.size(); i++) {
        if (i % 2 == 0) {
            blocks.emplace_back(v_ans.size(), nums[i]);
            for (int j = 0; j < nums[i]; j++) {
                v_ans.push_back(i / 2);
            }
        } else {
            spaces.emplace_back(v_ans.size(), nums[i]);
            for (int j = 0; j < nums[i]; j++) {
                v_ans.push_back(0);
            }
        }
    }
    for (int i = blocks.size() - 1; i >= 0; i--) {
        auto& [blk_idx, blk_sz] = blocks[i];
        for (auto& [space_idx, space_sz] : spaces) {
            if (blk_idx <= space_idx) continue;
            if (blk_sz <= space_sz) {
                for (int k = 0; k < blk_sz; k++) {
                    v_ans[space_idx + k] = i;
                    v_ans[blk_idx + k] = 0;
                }
                space_idx += blk_sz; space_sz -= blk_sz;
                break;
            }
        }
    }
    for (int i = 0; i < v_ans.size(); i++) {
        ans += v_ans[i] * i;
    }
    cout << ans << '\n';
}
