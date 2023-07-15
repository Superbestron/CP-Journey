#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, arr[5], maxi = 0, ans = 0; cin >> n;
    unordered_map<string, int> m;
    while (n--) {
        for (int i = 0; i < 5; i++) cin >> arr[i];
        sort(arr, arr + 5);
        string s;
        for (int i = 0; i < 5; i++) s += to_string(arr[i]);
        m[s]++;
    }
    for (auto& p : m) {
        if (p.second > maxi) {
            maxi = p.second;
            ans = p.second;
        } else if (p.second == maxi) {
            ans += p.second;
        }
    }
    cout << ans;
}
