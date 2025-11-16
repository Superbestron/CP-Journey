#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Use a flag to keep track of state i.e. increasing/decreasing.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ans = 0, x;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> nums;
        while (iss >> x) nums.push_back(x);
        bool increasing = true, can = true;
        if (abs(nums[1] - nums[0]) > 3) can = false;
        if (nums[1] < nums[0]) increasing = false;
        else if (nums[1] == nums[0]) can = false;
        int prev = nums[1];
        for (int i = 2; i < nums.size(); i++) {
            if (increasing) {
                if (nums[i] <= prev) can = false;
            } else {
                if (nums[i] >= prev) can = false;
            }
            if (abs(prev - nums[i]) > 3) can = false;
            prev = nums[i];
        }
        if (can) ans++;
    }
    cout << ans << '\n';
}
