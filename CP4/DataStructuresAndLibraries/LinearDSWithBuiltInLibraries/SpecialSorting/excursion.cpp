#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    string num;
    cin >> num;
    long ans = 0, ctr = 0;
    for (char c : num) {
        if (c == '1' || c == '2') {
            ctr++;
        } else {
            ans += ctr;
        }
    }
    ctr = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        if (num[i] == '1') {
            ctr++;
        }
        else if (num[i] == '2') {
            ans += ctr;
        }
    }
    cout << ans;
}
