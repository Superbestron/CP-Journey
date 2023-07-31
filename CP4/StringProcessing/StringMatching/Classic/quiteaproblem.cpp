#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        cout << (s.find("PROBLEM") == string::npos ? "no\n" : "yes\n");
    }
}