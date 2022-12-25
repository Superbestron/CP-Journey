#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    while (cin >> s1 >> s2 && (s1 != "0" || s2 != "0")) {
        int ans = 0;
        bool carry = false;
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        int diff = abs(static_cast<int>(s1.size()) - static_cast<int>(s2.size()));
        for (int i = 0; i < diff; i++) {
            if (s1.size() > s2.size()) s2 += '0';
            else s1 += '0';
        }
        for (int i = 0; i < s1.size(); i++) {
            int temp = 0;
            if (carry) {
                temp++;
                ans++;
            }
            temp += s1[i] - '0' + s2[i] - '0';
            if (temp >= 10) carry = true;
            else carry = false;
        }
        if (carry) ans++;
        if (ans == 0) cout << "No carry operation.";
        else if (ans == 1) cout << ans << " carry operation.";
        else cout << ans << " carry operations.";
        cout << endl;
    }
}