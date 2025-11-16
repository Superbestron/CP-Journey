#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Write a simple parser and advance string pointer accordingly, brute-forceable without needing to resort to KMP style
// string manipulations.

int mul(string& s, int& pos) {
    if (pos + 4 >= s.size()) return -1;
    if (s[pos] != 'm' || s[pos + 1] != 'u' || s[pos + 2] != 'l' || s[pos + 3] != '(') return -1;
    pos += 4;
    string temp;
    while (pos < s.size() && isdigit(s[pos])) {
        temp += s[pos];
        pos++;
    }
    int num1 = stoi(temp);
    if (pos >= s.size() || s[pos] != ',') return -1;
    pos++;
    temp.clear();
    while (pos < s.size() && isdigit(s[pos])) {
        temp += s[pos];
        pos++;
    }
    int num2 = stoi(temp);
    if (pos >= s.size() || s[pos] != ')') return -1;
    return num1 * num2;
}

int main() {
    string s;
    int ans = 0;
    while (cin >> s) {
        for (int i = 0; i < s.size(); ++i) {
            int new_i = i;
            int m = mul(s, new_i);
            if (m >= 0) {
                ans += m;
                i = new_i;
            }
        }
    }
    cout << ans << '\n';
}
