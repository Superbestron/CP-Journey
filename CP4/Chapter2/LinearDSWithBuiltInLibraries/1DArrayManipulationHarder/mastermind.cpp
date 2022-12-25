#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    vector<int> a(26);
    fill(a.begin(), a.end(), 0);
    int n, r = 0, s = 0;
    string s1, s2;
    cin >> n >> s1 >> s2;
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) {
            r++;
        } else {
            a[s1[i] - 'A']++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i] && a[s2[i] - 'A']-- > 0) {
            s++;
        }
    }
    cout << r << ' ' << s;
}