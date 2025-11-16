#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Use 2A as subroutine and brute force all possible removals of level.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ans = 0, x;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> nums;
        while (iss >> x) nums.push_back(x);
        for (int i = 0; i <= nums.size(); i++) {
            vi a;
            for (int j = 0; j < nums.size(); j++) {
                if (i == j) continue;
                a.push_back(nums[j]);
            }
            bool increasing = true, can = true;
            if (abs(a[1] - a[0]) > 3) can = false;
            if (a[1] < a[0]) increasing = false;
            else if (a[1] == a[0]) can = false;
            int prev = a[1];
            for (int i = 2; i < a.size(); i++) {
                if (increasing) {
                    if (a[i] <= prev) can = false;
                } else {
                    if (a[i] >= prev) can = false;
                }
                if (abs(prev - a[i]) > 3) can = false;
                prev = a[i];
            }
            if (can) {
                ans++;
                break;
            }
        }

    }
    cout << ans << '\n';
}
