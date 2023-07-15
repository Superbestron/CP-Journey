#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int L, x, val, cnt = 0, ans = 0;
    string s;
    cin >> L >> x;
    while (x--) {
        cin >> s >> val;
        if (s[0] == 'e') {
            if (cnt + val <= L) cnt += val;
            else ans++;
        } else cnt -= val;
    }
    cout << ans;
}