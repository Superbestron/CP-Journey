#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<int> ms;
    int maxi = 0, ans = 0;
    while (getline(cin, s) && s != "0") {
        int sz = s.size();
        maxi = max(maxi, sz);
        ms.push_back(sz);
    }
    ms.pop_back();
    for (int m : ms) ans += (maxi - m) * (maxi - m);
    cout << ans;
}