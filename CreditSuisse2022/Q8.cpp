#include <bits/stdc++.h>
using namespace std;

int solution(int n, int m, vector<int>& costs) {
    if (n == 0 || m < 2) return 0;
    int rsum = 0, count = 0, prev = costs[0], i = 0;
    vector<int> diff_arr;
    bool asc = true;
    while (++i < m) {
        if (costs[i] == prev) continue;
        if (asc) {
            if (prev > costs[i]) {
                if (i != 1) {
                    diff_arr.push_back(rsum);
                    count++;
                }
                asc = false;
                rsum = costs[i] - prev;
            } else rsum += costs[i] - prev;
        } else {
            if (prev < costs[i]) {
                // dont start with desc for diff_arr
                if (count != 0) diff_arr.push_back(rsum);
                asc = true;
                rsum = costs[i] - prev;
            } else {
                rsum += costs[i] - prev;
            }
        }
        prev = costs[i];
    }

    if (rsum > 0) {
        diff_arr.push_back(rsum);
        count++;
    }

    while (count-- > n) {
        int min = INT32_MAX, idx = -1;
        for (i = 0; i < diff_arr.size(); i++){
            if (abs(diff_arr[i]) < min){
                min = abs(diff_arr[i]);
                idx = i;
            }
        }
        if (idx == 0) {
            diff_arr.erase(diff_arr.begin(), diff_arr.begin() + 2);
        } else if (idx == diff_arr.size() - 1) {
            diff_arr.pop_back();
            diff_arr.pop_back();
        } else {
            diff_arr[idx - 1] += diff_arr[idx + 1] + diff_arr[idx];
            diff_arr.erase(diff_arr.begin() + idx, diff_arr.begin() + idx + 2);
        }
    }
    int ans = 0;
    for (auto& diff : diff_arr) {
        ans += diff > 0 ? diff : 0;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> costs(m, 0);
    for(int i = 0; i < m; i++){
        cin >> costs[i];
    }
    cout << solution(n, m, costs) << '\n';
}