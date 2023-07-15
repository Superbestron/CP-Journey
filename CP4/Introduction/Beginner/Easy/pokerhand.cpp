#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int arr[13], idx, ans = 0;
    memset(arr, 0, sizeof arr);
    string s;
    for (int i = 0; i < 5; i++) {
        cin >> s;
        if (s[0] == 'A') idx = 0;
        else if (s[0] == 'T') idx = 9;
        else if (s[0] == 'J') idx = 10;
        else if (s[0] == 'Q') idx = 11;
        else if (s[0] == 'K') idx = 12;
        else idx = s[0] - '1';
        arr[idx]++;
        ans = max(ans, arr[idx]);
    }
    cout << ans;
}