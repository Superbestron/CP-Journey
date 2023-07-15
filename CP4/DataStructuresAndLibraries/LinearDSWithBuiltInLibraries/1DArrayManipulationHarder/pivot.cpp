#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, maxi = 0, mini = 999999, curr, ans = 0;
    cin >> n;
    vector<int> a;
    unordered_set<int> s;
    while (n-- > 0) {
        cin >> curr;
        a.push_back(curr);
        if (curr > maxi) {
            s.insert(curr);
        }
        maxi = max(maxi, curr);
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] < mini) {
            if (s.count(a[i]) != 0) ans++;
        }
        mini = min(mini, a[i]);
    }
    cout << ans;
}