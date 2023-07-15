#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    getline(cin, s);
    cout << (s == "OCT 31" || s == "DEC 25" ? "yup" : "nope");
}