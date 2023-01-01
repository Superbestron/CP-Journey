#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int max = 0;
    string s, ans;
    unordered_map<string, int> m;
    while (getline(cin, s) && s != "***") {
        m[s]++;
        if (m[s] > max) {
            max = m[s];
            ans = s;
        } else if (m[s] == max) ans = "Runoff!";
    }
    cout << ans;
}
