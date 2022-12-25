#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, prev, curr, ans = 0;
    cin >> n;
    unordered_map<int, int> s;
    while (n-- > 0) {
        cin >> curr;
        if (s[curr] == 0) {
            ans++;
        } else {
            s[curr]--;
        }
        s[curr - 1]++;
    }
    cout << ans;
}