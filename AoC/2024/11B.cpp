#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// We need to be a bit smarter here. If you think carefully, we can actually isolate each stone as it is, and
// calculate how many stones it will end up with after a set number of blinks, and notice that there are a lot of
// repeated computations especially if the stone is 0. With these findings, we can memoise the solution of each stone
// based on its current number and the number of blinks left. What's left is to add the solution of each dp call of
// each stone in the starting stone list.

unordered_map<ll, vll> memo;

ll dp(ll num, int times) {
    if (times == 0) return 1;
    if (memo.count(num)) {
        if (memo[num][times] != -1) {
            return memo[num][times];
        }
    } else {
        memo[num].assign(76, -1);
    }
    ll& ans = memo[num][times];
    if (num == 0) {
        return ans = dp(1, times - 1);
    } else if (to_string(num).length() % 2 == 0) {
        string t = to_string(num);
        int len = t.length();
        return ans = dp(stoll(t.substr(0, len / 2)), times - 1) + dp(stoll(t.substr(len / 2, len / 2)), times - 1);
    } else {
        return ans = dp(num * 2024, times - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    ll val, ans = 0;
    vll v, v2;
    while (cin >> val) v.push_back(val);
    for (long long i : v) {
        ans += dp(i, 75);
    }
    cout << ans << '\n';
}
