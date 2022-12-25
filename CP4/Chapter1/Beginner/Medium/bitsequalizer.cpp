#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    int c, ans;
    cin >> c;
    for (int j = 1; j <= c; j++) {
        int zero_one = 0, one_zero = 0, qn_one = 0, qn_zero = 0;
        cin >> s >> t;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                if (s[i] == '0' and t[i] == '1') zero_one++;
                else if (s[i] == '1' and t[i] == '0') one_zero++;
                else if (s[i] == '?' and t[i] == '1') qn_one++;
                else qn_zero++;
            }
        }
        // swap first -> 01 and 10 should be only 1 move
        ans = min(zero_one, one_zero);
        zero_one -= ans;
        one_zero -= ans;

        if (zero_one) ans += zero_one + qn_one + qn_zero;
        else {
            // if more "1:0" pairings then "?:1", impossible
            if (one_zero > qn_one) ans = -1;
            else ans += one_zero + qn_one + qn_zero;
        }

        cout << "Case " << j << ": " << ans << endl;
    }
}