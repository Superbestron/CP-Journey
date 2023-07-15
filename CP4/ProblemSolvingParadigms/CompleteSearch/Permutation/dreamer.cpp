#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int arr[8], ans = 0;
        char c;
        bool printed = false;
        string earliest;
        for (int i = 0; i < 8; i++) {
            cin >> c;
            arr[i] = c - '0';
        }

        sort(arr, arr + 8);
        do {
            int day = arr[6] * 10 + arr[7];
            int month = arr[4] * 10 + arr[5];
            int year = arr[0] * 1000 + arr[1] * 100 + arr[2] * 10 + arr[3];
            if (day == 0 || month == 0 || year < 2000) continue;
            if (month > 12) continue;
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                if (day > 31) continue;
            } else if (month == 4 || month == 6 || month == 9 || month == 11) {
                if (day > 30) continue;
            } else {
                bool leap;
                if (year % 400 == 0) {
                    leap = true;
                } else if (year % 100 == 0) {
                    leap = false;
                } else if (year % 4 == 0) {
                    leap = true;
                } else {
                    leap = false;
                }
                if (leap) {
                    if (day > 29) continue;
                }
                else {
                    if (day > 28) continue;
                }
            }
            if (!printed) {
                earliest += string(2 - min(2, (int) to_string(day).length()), '0') + to_string(day) + " "
                        + string(2 - min(2, (int) to_string(month).length()), '0') + to_string(month) + " "
                        + string(4 - min(4, (int) to_string(year).length()), '0') + to_string(year);
                printed = true;
            }
            ans++;
        } while (next_permutation(arr, arr + 8));
        if (ans == 0) cout << 0 << '\n';
        else cout << ans << ' ' << earliest << '\n';
    }
}
