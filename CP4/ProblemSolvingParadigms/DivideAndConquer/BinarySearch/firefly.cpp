#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h, ans = 0, mini = 9999999; cin >> n >> h;
    vector<int> stalagmites, stalactites;
    for (int i = 0; i < n; i++) {
        int temp; cin >> temp;
        if (i % 2) stalactites.push_back(temp);
        else stalagmites.push_back(temp);
    }
    sort(stalagmites.begin(), stalagmites.end());
    sort(stalactites.begin(), stalactites.end());
    for (int i = 1; i <= h; i++) {
        // >= x
        auto it = lower_bound(stalagmites.begin(), stalagmites.end(), i);
        int count = static_cast<int>(stalagmites.end() - it);

        auto it2 = lower_bound(stalactites.begin(), stalactites.end(), h - i + 1);
        count += static_cast<int>(stalactites.end() - it2);

       if (count == mini) ans++;
        else if (count < mini) {
            ans = 1;
            mini = count;
        }
    }
    cout << mini << ' ' << ans;
}