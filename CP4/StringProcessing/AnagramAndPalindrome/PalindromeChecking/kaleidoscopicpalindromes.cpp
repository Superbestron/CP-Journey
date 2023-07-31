#include <bits/stdc++.h>

using namespace std;

inline string convert_to_base(int n, int k) {
    string ans;
    while (n) {
        ans += static_cast<char>(n % k + '0');
        n /= k;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

inline bool check_palindrome(string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - i - 1]) return false;
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, k, ans = 0;
    cin >> a >> b >> k;
    for (int j = a; j <= b; j++) {
        bool can = true;
        for (int i = 2; i <= k; i++) {
            string str = convert_to_base(j, i);
            if (!check_palindrome(str)) {
                can = false;
                break;
            }
        }
        if (can) ans++;
    }
    cout << ans;
}